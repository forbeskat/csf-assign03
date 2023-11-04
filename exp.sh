#!/bin/bash

# Set up the configurations you want to test
NUM_SETS=(1 32)
NUM_BLOCKS=(1 4 8 16 32)
NUM_BYTES=32
WRITE_POLICY=("write-through" "write-back")
ALLOCATION_POLICY=("no-write-allocate" "write-allocate")
EVICT_POLICY=("fifo" "lru")

# Path to your cache simulator executable
CACHE_SIMULATOR="./csim"

# Input trace file
INPUT_TRACE_FILE="gcc.trace"

# Create an array to store miss rates for each configuration
declare -A MISS_RATES

for num_sets in "${NUM_SETS[@]}"; do
  for num_blocks in "${NUM_BLOCKS[@]}"; do
    for write_policy in "${WRITE_POLICY[@]}"; do
      for allocation_policy in "${ALLOCATION_POLICY[@]}"; do
        for eviction_policy in "${EVICT_POLICY[@]}"; do
          echo "Running with Num Sets: $num_sets, Num Blocks: $num_blocks, Write Policy: $write_policy, Allocation Policy: $allocation_policy, Eviction Policy: $eviction_policy"
          output=$("$CACHE_SIMULATOR" "$num_sets" "$num_blocks" "$NUM_BYTES" "$allocation_policy" "$write_policy" "$eviction_policy" < "$INPUT_TRACE_FILE")
          load_misses=$(grep -o "Load misses: [0-9]*" <<< "$output" | grep -o "[0-9]*")
          total_cycles=$(grep -o "Total cycles: [0-9]*" <<< "$output" | grep -o "[0-9]*")
          miss_rate=$(echo "scale=7; $load_misses / $total_cycles" | bc)
          echo "Miss rate: $miss_rate"
          echo "csim output:"
          echo "$output"
          echo "-----------------------------------------------------"
          MISS_RATES["$num_sets-$num_blocks-$write_policy-$allocation_policy-$eviction_policy"]="$miss_rate"
        done
      done
    done
  done
done

# Print a summary of miss rates and configurations
echo "summary (config vs miss rate):"
for config in "${!MISS_RATES[@]}"; do
  miss_rate="${MISS_RATES[$config]}"
  # Extract Num Sets, Num Blocks, Write Policy, Allocation Policy, and Eviction Policy from the configuration string
  IFS='-' read -r -a config_parts <<< "$config"
  num_sets="${config_parts[0]}"
  num_blocks="${config_parts[1]}"
  write_policy="${config_parts[2]}-${config_parts[3]}"
  allocation_policy="${config_parts[4]}-${config_parts[5]}"
  eviction_policy="${config_parts[6]}"
  echo "sets: $num_sets, blocks: $num_blocks, $write_policy, $allocation_policy $eviction_policy ${config_parts[7]}     miss rate: $miss_rate"
done
