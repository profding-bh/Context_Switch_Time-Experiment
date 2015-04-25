The name of our executable is mylocks. To compile the code,
just type "make" into the command prompt. To run the executable,
type ./mylocks -t -i -d, where t=threads, i=iterations, d=testid.
Ex: ./mylocks -4 -1000000 -0
In order to call the default "mylocks" program, just type
./mylocks into the command prompt.


----MEASUREMENTS-----

----# THREADS VS TIME--------
Pthread Mutex	
Threads	Time (ms)
	1	29
	2	150
	3	434
	4	811
	5	1089
	6	1208
	7	1428
	8	1603

Pthread SpinMutex
Threads	Time
	1	9
	2	45
	3	106
	4	165
	5	240
	6	308
	7	395
	8	503

MySpinTAS	
Threads	Time
	1	16
	2	214
	3	566
	4	755
	5	1577
	6	1935
	7	2923
	8	3057

MySpinTTAS
Threads	Time
	1	17
	2	138
	3	302
	4	425
	5	647
	6	846
	7	1067
	8	1408

MyMutexTAS	
Threads	Time
	1	17
	2	38
	3	56
	4	107
	5	168
	6	222
	7	284
	8	511

MyMutexTTAS	
Threads	Time
	1	18
	2	35
	3	53
	4	72
	5	100
	6	123
	7	267
	8	283




----LOG(ITERATIONS) VS LOG(TIME(ns))---------

Pthread Mutex	
Iterations		Time (ms)
	10			18730
	100			1631
	1000		171
	10000		477
	100000		364
	1000000		800
	10000000	801
	100000000	821

Pthread SpinMutex	
Iterations		Time
	10			9006
	100			670
	1000		87
	10000		405
	100000		155
	1000000		208
	10000000	165
	100000000	163

MySpinTAS	
Iterations		Time
	10			4671
	100			1432
	1000		101
	10000		1007
	100000		1156
	1000000		1018
	10000000	954
	100000000	997

MySpinTTAS	
Iterations		Time
	10			11007
	100			1092
	1000		104
	10000		478
	100000		499
	1000000		458
	10000000	418
	100000000	418

MyMutexTAS	
Iterations		Time
	10			7538
	100			823
	1000		104
	10000		1609
	100000		128
	1000000		151
	10000000	78
	100000000	117

MyMutexTTAS	
Iterations		Time
	10			5834
	100			1194
	1000		104
	10000		81
	100000		72
	1000000		126
	10000000	73
	100000000	113










