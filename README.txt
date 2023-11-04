# csf-assign03

Milestone 1:

Katherine - Makefile
Annie - main

Milestone 2:

Katherine - set up data structures and input handling, worked on the body of the assignment 
Annie - index/tag/offset handling, worked on the body of the assignment

Milestone 3:
Katherine - debugging + refactored everything
Annie - debugging + refactored everything, wrote script for experiments, improved simplicity/efficiency of code
Dave Hovenmeyer - changed 2 variable names that +40'ed the autograder, alleviated pain

####################################################################################################

For our experiments, we essentially created caches with all possible combinations for the configurations of the same size cache 
for multiple cache sizes. To find the best configuration, we must consider the drawbacks of fully associative caches (infeasible 
hardware requirements) and direct mapped caches (high miss rate) to find an equilbrium between cycle counts and overhead.

We start with a cache with an arbitrary block size, and created a cache with 32 sets containing 1 block each,
with 32 bytes per block. This is a direct mapped cache.

After that, we created a cache with 1 set containing 32 blocks each, with 32 bytes per block. 
This is a fully associative cache.

Lastly, we created a cache with 32 sets containing 8 blocks each, with 32 bytes per block. 
This is an 8-way set associative cache.

For each cache size, we would compare the different cache configurations for each cache size 
to determine which version was better based on miss rate as well as total cycles.

Conclusion:

We found that out of all of the possible configurations, that the absolute best 
cache configuration in the context of this assignment was a write-allocate, write-back, and LRU configuration.
We consistently found that write-allocate, write-back, and LRU was the best or close to the best 
configuration for the cache. Additionally, we found that a fully associative cache was the fastest.

Experimental Results:
If you scroll further you can find a basic raw summary of all results and the raw output of the script.


.................................................
raw summary of data (nonsensical write-back no-write-allocated combo excluded)
.................................................

summary (config vs miss rate):
sets: 32, blocks: 4, write-through, write-allocate fifo      miss rate: .0002681
sets: 1, blocks: 16, write-through, write-allocate lru      miss rate: .0006633
sets: 1, blocks: 1, write-through, write-allocate fifo      miss rate: .0007873
sets: 32, blocks: 32, write-through, write-allocate lru      miss rate: .000781 
sets: 1, blocks: 16, write-back, write-allocate fifo      miss rate: .0006331
sets: 32, blocks: 8, write-through, no-write allocate lru     miss rate: .0002124
sets: 1, blocks: 1, write-back, write-allocate lru      miss rate: .0006176
sets: 32, blocks: 16, write-through, write-allocate fifo      miss rate: .0001118
sets: 1, blocks: 8, write-back, write-allocate fifo      miss rate: .0006455
sets: 32, blocks: 16, write-back, write-allocate fifo      miss rate: .0002624
sets: 1, blocks: 32, write-through, no-write allocate fifo     miss rate: .0006834
sets: 1, blocks: 32, write-back, write-allocate lru      miss rate: .0006112
sets: 32, blocks: 32, write-through, no-write allocate fifo     miss rate: .0001840
sets: 1, blocks: 16, write-through, no-write allocate fifo     miss rate: .0008750
sets: 32, blocks: 8, write-through, no-write allocate fifo     miss rate: .0002476
sets: 32, blocks: 4, write-through, no-write allocate lru     miss rate: .0003178
sets: 1, blocks: 32, write-through, write-allocate fifo      miss rate: .0005407
sets: 32, blocks: 1, write-back, write-allocate fifo      miss rate: .0006757
sets: 1, blocks: 32, write-through, no-write allocate lru     miss rate: .0006164
sets: 1, blocks: 16, write-through, write-allocate fifo      miss rate: .0006864
sets: 1, blocks: 1, write-through, write-allocate lru      miss rate: .0007873
sets: 32, blocks: 32, write-through, no-write allocate lru     miss rate: .0001739
sets: 1, blocks: 1, write-through, no-write allocate fifo     miss rate: .0011194
sets: 1, blocks: 1, write-through, no-write allocate lru     miss rate: .0011194
sets: 32, blocks: 8, write-back, write-allocate fifo      miss rate: .0003237
sets: 32, blocks: 1, write-back, write-allocate lru      miss rate: .0006757
sets: 1, blocks: 32, write-through, write-allocate lru      miss rate: .0004945
sets: 1, blocks: 4, write-through, no-write allocate fifo     miss rate: .0010757
sets: 1, blocks: 4, write-through, write-allocate lru      miss rate: .0008144
sets: 1, blocks: 8, write-through, write-allocate lru      miss rate: .0008211
sets: 1, blocks: 4, write-through, no-write allocate lru     miss rate: .0010762
sets: 1, blocks: 4, write-back, write-allocate lru      miss rate: .0006624
sets: 32, blocks: 1, write-through, write-allocate lru      miss rate: .0007155
sets: 32, blocks: 1, write-through, no-write allocate fifo     miss rate: .0008800
sets: 1, blocks: 8, write-through, write-allocate fifo      miss rate: .0008012
sets: 1, blocks: 8, write-through, no-write allocate lru     miss rate: .0010125
sets: 1, blocks: 8, write-back, write-allocate lru      miss rate: .0006919
sets: 32, blocks: 8, write-through, write-allocate fifo      miss rate: .0001542
sets: 32, blocks: 4, write-through, no-write allocate fifo     miss rate: .0003662
sets: 32, blocks: 4, write-back, write-allocate fifo      miss rate: .0004545
sets: 1, blocks: 4, write-back, write-allocate fifo      miss rate: .0006628
sets: 1, blocks: 4, write-through, write-allocate fifo      miss rate: .0008143
sets: 32, blocks: 16, write-through, no-write allocate fifo     miss rate: .0002058
sets: 1, blocks: 32, write-back, write-allocate fifo      miss rate: .0006029
sets: 32, blocks: 4, write-back, write-allocate lru      miss rate: .0004159
sets: 1, blocks: 8, write-through, no-write allocate fifo     miss rate: .0010305
sets: 32, blocks: 32, write-back, write-allocate lru      miss rate: .0002113
sets: 32, blocks: 1, write-through, write-allocate fifo      miss rate: .0007155
sets: 32, blocks: 8, write-back, write-allocate lru      miss rate: .0002740
sets: 1, blocks: 16, write-back, write-allocate lru      miss rate: .0006771
sets: 32, blocks: 32, write-through, write-allocate fifo      miss rate: .000894
sets: 32, blocks: 16, write-through, write-allocate lru      miss rate: .000908
sets: 32, blocks: 4, write-through, write-allocate lru      miss rate: .0002227
sets: 1, blocks: 1, write-back, write-allocate fifo      miss rate: .00006176
sets: 32, blocks: 16, write-through, no-write allocate lru     miss rate: .0001846
sets: 1, blocks: 16, write-through, no-write allocate lru     miss rate: .0008192
sets: 32, blocks: 32, write-back, write-allocate fifo      miss rate: .0002334
sets: 32, blocks: 1, write-through, no-write allocate lru     miss rate: .0008800
sets: 32, blocks: 8, write-through, write-allocate lru      miss rate: .0001198
sets: 32, blocks: 16, write-back, write-allocate lru      miss rate: .0002253


.................................................
all raw results from script pasted from terminal:
.................................................

[awang105@ugrad17 csf-assign03]$ ./exp.sh
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0011194
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 105414
Load misses: 212783
Store hits: 34709
Store misses: 162777
Total cycles: 190080414
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0011194
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 105414
Load misses: 212783
Store hits: 34709
Store misses: 162777
Total cycles: 190080414
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0007873
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 104421
Load misses: 213776
Store hits: 96673
Store misses: 100813
Total cycles: 271524221
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0007873
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 104421
Load misses: 213776
Store hits: 96673
Store misses: 100813
Total cycles: 271524221
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0006176
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 104421
Load misses: 213776
Store hits: 96673
Store misses: 100813
Total cycles: 346119507
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 1, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0006176
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 104421
Load misses: 213776
Store hits: 96673
Store misses: 100813
Total cycles: 346119507
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0010757
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 164561
Load misses: 153636
Store hits: 75521
Store misses: 121965
Total cycles: 142821961
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0010762
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 163991
Load misses: 154206
Store hits: 80486
Store misses: 117000
Total cycles: 143277391
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0008143
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 168068
Load misses: 150129
Store hits: 142064
Store misses: 55422
Total cycles: 184357468
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0008144
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 164735
Load misses: 153462
Store hits: 140315
Store misses: 57171
Total cycles: 188419735
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0006628
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 168068
Load misses: 150129
Store hits: 142064
Store misses: 55422
Total cycles: 226487954
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 4, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0006624
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 164735
Load misses: 153462
Store hits: 140315
Store misses: 57171
Total cycles: 231655021
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0010305
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 201120
Load misses: 117077
Store hits: 117520
Store misses: 79966
Total cycles: 113611320
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0010125
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 211820
Load misses: 106377
Store hits: 126885
Store misses: 70601
Total cycles: 105062020
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0008012
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 211024
Load misses: 107173
Store hits: 162415
Store misses: 35071
Total cycles: 133754824
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0008211
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 216755
Load misses: 101442
Store hits: 169464
Store misses: 28022
Total cycles: 123536555
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0006455
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 211024
Load misses: 107173
Store hits: 162415
Store misses: 35071
Total cycles: 166019710
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 8, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0006919
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 216755
Load misses: 101442
Store hits: 169464
Store misses: 28022
Total cycles: 146602241
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0008750
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 259837
Load misses: 58360
Store hits: 145329
Store misses: 52157
Total cycles: 66696437
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0008192
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 270600
Load misses: 47597
Store hits: 150222
Store misses: 47264
Total cycles: 58096800
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0006864
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 264756
Load misses: 53441
Store hits: 178630
Store misses: 18856
Total cycles: 77850956
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0006633
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 274063
Load misses: 44134
Store hits: 183488
Store misses: 13998
Total cycles: 66528263
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0006331
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 264756
Load misses: 53441
Store hits: 178630
Store misses: 18856
Total cycles: 84403042
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 16, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0006771
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 274063
Load misses: 44134
Store hits: 183488
Store misses: 13998
Total cycles: 65174749
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0006834
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 287980
Load misses: 30217
Store hits: 155705
Store misses: 41781
Total cycles: 44210180
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0006164
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 293818
Load misses: 24379
Store hits: 159515
Store misses: 37971
Total cycles: 39545618
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0005407
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 290901
Load misses: 27296
Store hits: 186734
Store misses: 10752
Total cycles: 50477901
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0004945
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 295815
Load misses: 22382
Store hits: 188350
Store misses: 9136
Total cycles: 45258815
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0006029
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 290901
Load misses: 27296
Store hits: 186734
Store misses: 10752
Total cycles: 45270787
-----------------------------------------------------
Running with Num Sets: 1, Num Blocks: 32, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0006112
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 295815
Load misses: 22382
Store hits: 188350
Store misses: 9136
Total cycles: 36617301
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0008800
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 258704
Load misses: 59493
Store hits: 136245
Store misses: 61241
Total cycles: 67601704
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0008800
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 258704
Load misses: 59493
Store hits: 136245
Store misses: 61241
Total cycles: 67601704
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0007155
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 259082
Load misses: 59115
Store hits: 178338
Store misses: 19148
Total cycles: 82618082
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0007155
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 259082
Load misses: 59115
Store hits: 178338
Store misses: 19148
Total cycles: 82618082
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0006757
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 259082
Load misses: 59115
Store hits: 178338
Store misses: 19148
Total cycles: 87482968
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 1, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0006757
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 259082
Load misses: 59115
Store hits: 178338
Store misses: 19148
Total cycles: 87482968
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0003662
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 307806
Load misses: 10391
Store hits: 164677
Store misses: 32809
Total cycles: 28369206
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0003178
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 309647
Load misses: 8550
Store hits: 167477
Store misses: 30009
Total cycles: 26898247
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0002681
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 309693
Load misses: 8504
Store hits: 191425
Store misses: 6061
Total cycles: 31710293
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0002227
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 311538
Load misses: 6659
Store hits: 191860
Store misses: 5626
Total cycles: 29888138
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0004545
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 309693
Load misses: 8504
Store hits: 191425
Store misses: 6061
Total cycles: 18708779
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 4, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0004159
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 311538
Load misses: 6659
Store hits: 191860
Store misses: 5626
Total cycles: 16009824
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0002476
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 312002
Load misses: 6195
Store hits: 167214
Store misses: 30272
Total cycles: 25016602
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0002124
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 313061
Load misses: 5136
Store hits: 168872
Store misses: 28614
Total cycles: 24170461
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0001542
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 313929
Load misses: 4268
Store hits: 192244
Store misses: 5242
Total cycles: 27670529
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0001198
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315006
Load misses: 3191
Store hits: 192487
Store misses: 4999
Total cycles: 26615606
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0003237
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 313929
Load misses: 4268
Store hits: 192244
Store misses: 5242
Total cycles: 13181015
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 8, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0002740
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315006
Load misses: 3191
Store hits: 192487
Store misses: 4999
Total cycles: 11642092
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0002058
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 313253
Load misses: 4944
Store hits: 168970
Store misses: 28516
Total cycles: 24017053
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0001846
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 313851
Load misses: 4346
Store hits: 169219
Store misses: 28267
Total cycles: 23539251
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0001118
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315248
Load misses: 2949
Store hits: 192558
Store misses: 4928
Total cycles: 26365448
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0000908
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315853
Load misses: 2344
Store hits: 192672
Store misses: 4814
Total cycles: 25790853
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0002624
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315248
Load misses: 2949
Store hits: 192558
Store misses: 4928
Total cycles: 11235934
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 16, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0002253
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315853
Load misses: 2344
Store hits: 192672
Store misses: 4814
Total cycles: 10402139
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Miss rate: .0001840
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 313868
Load misses: 4329
Store hits: 169235
Store misses: 28251
Total cycles: 23525668
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-through, Allocation Policy: no-write-allocate, Eviction Policy: lru
Miss rate: .0001739
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 314144
Load misses: 4053
Store hits: 169570
Store misses: 27916
Total cycles: 23305144
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0000894
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315902
Load misses: 2295
Store hits: 192803
Store misses: 4683
Total cycles: 25646902
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-through, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0000781
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 316216
Load misses: 1981
Store hits: 192869
Store misses: 4617
Total cycles: 25343216
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: fifo
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-back, Allocation Policy: no-write-allocate, Eviction Policy: lru
Write-back and no-write-allocate is not an available configuration.
(standard_in) 1: syntax error
Miss rate: 
csim output:

-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: fifo
Miss rate: .0002334
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 315902
Load misses: 2295
Store hits: 192803
Store misses: 4683
Total cycles: 9832588
-----------------------------------------------------
Running with Num Sets: 32, Num Blocks: 32, Write Policy: write-back, Allocation Policy: write-allocate, Eviction Policy: lru
Miss rate: .0002113
csim output:
Total loads: 318197
Total stores: 197486
Load hits: 316216
Load misses: 1981
Store hits: 192869
Store misses: 4617
Total cycles: 9374502
-----------------------------------------------------
summary (config vs miss rate):
sets: 32, blocks: 4, write-through, write-allocate fifo      miss rate: .0002681
sets: 1, blocks: 16, write-through, write-allocate lru      miss rate: .0006633
sets: 32, blocks: 4, write-back, no-write allocate lru     miss rate: 
sets: 1, blocks: 1, write-through, write-allocate fifo      miss rate: .0007873
sets: 32, blocks: 32, write-through, write-allocate lru      miss rate: .0000781
sets: 1, blocks: 16, write-back, write-allocate fifo      miss rate: .0006331
sets: 32, blocks: 8, write-through, no-write allocate lru     miss rate: .0002124
sets: 1, blocks: 1, write-back, write-allocate lru      miss rate: .0006176
sets: 1, blocks: 4, write-back, no-write allocate lru     miss rate: 
sets: 32, blocks: 8, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 16, write-through, write-allocate fifo      miss rate: .0001118
sets: 1, blocks: 8, write-back, write-allocate fifo      miss rate: .0006455
sets: 32, blocks: 16, write-back, write-allocate fifo      miss rate: .0002624
sets: 32, blocks: 1, write-back, no-write allocate lru     miss rate: 
sets: 1, blocks: 32, write-back, no-write allocate lru     miss rate: 
sets: 1, blocks: 32, write-through, no-write allocate fifo     miss rate: .0006834
sets: 1, blocks: 32, write-back, write-allocate lru      miss rate: .0006112
sets: 32, blocks: 32, write-through, no-write allocate fifo     miss rate: .0001840
sets: 1, blocks: 16, write-through, no-write allocate fifo     miss rate: .0008750
sets: 1, blocks: 1, write-back, no-write allocate lru     miss rate: 
sets: 32, blocks: 8, write-through, no-write allocate fifo     miss rate: .0002476
sets: 1, blocks: 32, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 4, write-through, no-write allocate lru     miss rate: .0003178
sets: 1, blocks: 32, write-through, write-allocate fifo      miss rate: .0005407
sets: 32, blocks: 1, write-back, write-allocate fifo      miss rate: .0006757
sets: 1, blocks: 32, write-through, no-write allocate lru     miss rate: .0006164
sets: 1, blocks: 16, write-through, write-allocate fifo      miss rate: .0006864
sets: 1, blocks: 1, write-through, write-allocate lru      miss rate: .0007873
sets: 32, blocks: 32, write-through, no-write allocate lru     miss rate: .0001739
sets: 1, blocks: 1, write-through, no-write allocate fifo     miss rate: .0011194
sets: 1, blocks: 1, write-through, no-write allocate lru     miss rate: .0011194
sets: 32, blocks: 32, write-back, no-write allocate lru     miss rate: 
sets: 1, blocks: 4, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 8, write-back, write-allocate fifo      miss rate: .0003237
sets: 32, blocks: 1, write-back, write-allocate lru      miss rate: .0006757
sets: 1, blocks: 32, write-through, write-allocate lru      miss rate: .0004945
sets: 1, blocks: 4, write-through, no-write allocate fifo     miss rate: .0010757
sets: 1, blocks: 4, write-through, write-allocate lru      miss rate: .0008144
sets: 1, blocks: 8, write-through, write-allocate lru      miss rate: .0008211
sets: 32, blocks: 4, write-back, no-write allocate fifo     miss rate: 
sets: 1, blocks: 4, write-through, no-write allocate lru     miss rate: .0010762
sets: 32, blocks: 16, write-back, no-write allocate lru     miss rate: 
sets: 1, blocks: 4, write-back, write-allocate lru      miss rate: .0006624
sets: 32, blocks: 1, write-through, write-allocate lru      miss rate: .0007155
sets: 1, blocks: 16, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 16, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 8, write-back, no-write allocate lru     miss rate: 
sets: 1, blocks: 1, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 1, write-through, no-write allocate fifo     miss rate: .0008800
sets: 1, blocks: 8, write-through, write-allocate fifo      miss rate: .0008012
sets: 1, blocks: 8, write-through, no-write allocate lru     miss rate: .0010125
sets: 1, blocks: 8, write-back, no-write allocate lru     miss rate: 
sets: 32, blocks: 1, write-back, no-write allocate fifo     miss rate: 
sets: 1, blocks: 8, write-back, write-allocate lru      miss rate: .0006919
sets: 32, blocks: 8, write-through, write-allocate fifo      miss rate: .0001542
sets: 32, blocks: 4, write-through, no-write allocate fifo     miss rate: .0003662
sets: 32, blocks: 4, write-back, write-allocate fifo      miss rate: .0004545
sets: 1, blocks: 4, write-back, write-allocate fifo      miss rate: .0006628
sets: 1, blocks: 4, write-through, write-allocate fifo      miss rate: .0008143
sets: 32, blocks: 16, write-through, no-write allocate fifo     miss rate: .0002058
sets: 1, blocks: 32, write-back, write-allocate fifo      miss rate: .0006029
sets: 32, blocks: 4, write-back, write-allocate lru      miss rate: .0004159
sets: 1, blocks: 8, write-through, no-write allocate fifo     miss rate: .0010305
sets: 32, blocks: 32, write-back, write-allocate lru      miss rate: .0002113
sets: 32, blocks: 1, write-through, write-allocate fifo      miss rate: .0007155
sets: 32, blocks: 8, write-back, write-allocate lru      miss rate: .0002740
sets: 1, blocks: 16, write-back, write-allocate lru      miss rate: .0006771
sets: 32, blocks: 32, write-through, write-allocate fifo      miss rate: .0000894
sets: 32, blocks: 32, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 16, write-through, write-allocate lru      miss rate: .0000908
sets: 32, blocks: 4, write-through, write-allocate lru      miss rate: .0002227
sets: 1, blocks: 16, write-back, no-write allocate lru     miss rate: 
sets: 1, blocks: 1, write-back, write-allocate fifo      miss rate: .0006176
sets: 32, blocks: 16, write-through, no-write allocate lru     miss rate: .0001846
sets: 1, blocks: 16, write-through, no-write allocate lru     miss rate: .0008192
sets: 32, blocks: 32, write-back, write-allocate fifo      miss rate: .0002334
sets: 32, blocks: 1, write-through, no-write allocate lru     miss rate: .0008800
sets: 1, blocks: 8, write-back, no-write allocate fifo     miss rate: 
sets: 32, blocks: 8, write-through, write-allocate lru      miss rate: .0001198
sets: 32, blocks: 16, write-back, write-allocate lru      miss rate: .0002253


