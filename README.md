# SortingAlgorithms

### Synopsis

Finds sorting algorithm which best suits to sort a given text file. Some test are made to evaluate the effectiveness of 6 most popular sorting algorithms in sorting text files of sizes 100, 500, 1000, and 5000 words for random, reverse and sorted content. Also some tests are made for texts with high percent of duplicated words.

### Usage
```
Sort file and get full result (6 sorting algorithm): ./sortalgs -in <input file path> (-o <output file path>) 
Sort file with auto-recommended algorithm: ./sortalgs -in <input file path> (-o <output file path>)-r (-s - if stable sort is required)
Test new text files in 100-500-1000-5000 mode: ./sortalgs -in <input file path> (-o <output file path>) -test

GNU GCC compiler version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)
Thread model: posix
```

### Test results

######DURATION
```
RANDOMIZED INPUT
           	size = 5000	  size = 1000	  size = 500	  size = 100	
      Heap	0.000661966 	0.000104851 	5.8771e-05  	1.2489e-05  	
 Insertion	0.160327    	0.00499544  	0.00186785  	7.1695e-05  	
     Merge	0.299945    	0.0607869   	0.0326713   	0.00694746  	
     Quick	0.151837    	0.00672207  	0.00177262  	0.000102958 	
 Selection	0.372911    	0.0142988   	0.00351101  	0.000152925 	
     Shell	0.00141522  	0.000242571 	9.7443e-05  	2.5956e-05  	

REVERSED INPUT
           	size = 5000	  size = 1000	  size = 500	  size = 100
      Heap	0.000559708 	0.000102094 	6.0821e-05  	1.377e-05   	
 Insertion	0.192956    	0.00607154  	0.00216932  	9.5202e-05  	
     Merge	0.358881    	0.0668525   	0.0335178   	0.00772975  	
     Quick	0.135112    	0.00539428  	0.00138747  	8.6515e-05  	
 Selection	0.318013    	0.0126364   	0.00320386  	0.000145304 	
     Shell	0.0011446   	0.000184142 	8.1146e-05  	2.3262e-05  
     
SORTED INPUT     
Duration
           	size = 5000	  size = 1000	  size = 500	  size = 100
      Heap	0.000553114 	9.4361e-05  	0.000123806 	1.1167e-05  	
 Insertion	0.0890168   	0.000488451 	0.00105963  	2.321e-05   	
     Merge	0.330961    	0.0720307   	0.0345629   	0.00719202  	
     Quick	0.15757     	0.00639028  	0.00171645  	9.6904e-05  	
 Selection	0.353048    	0.0136835   	0.00354915  	0.000146788 	
     Shell	0.00119676  	0.00019703  	8.9537e-05  	5.8267e-05  	
```

######COMPARES
```
RANDOMIZED INPUT
           	size = 5000	  size = 1000	  size = 500	  size = 100	
      Heap	27112       	5344        	2672        	532         	
 Insertion	10130980    	312334      	105770      	3862        	
     Merge	86170       	13882       	6195        	889         	
     Quick	10361513    	480916      	124074      	5347        	
 Selection	12497502    	499502      	124752      	4952        	
     Shell	77542       	12944       	5546        	724         	

REVERSED INPUT
           	size = 5000	  size = 1000	  size = 500	  size = 100
      Heap	11016       	4502        	2108        	396         	
 Insertion	13517264    	420264      	136880      	5886        	
     Merge	86613       	13909       	6205        	889         	
     Quick	12517497    	503497      	126747      	5347        	
 Selection	12497502    	499502      	124752      	4952        	
     Shell	77542       	12944       	5546        	724   
     
SORTED INPUT     
Duration
           	size = 5000	  size = 1000	  size = 500	  size = 100
      Heap	31650       	5980        	3132        	402         	
 Insertion	4922234     	32380       	49878       	1202        	
     Merge	86613       	13909       	6205        	889         	
     Quick	12517497    	503497      	126747      	5347        	
 Selection	12497502    	499502      	124752      	4952        	
     Shell	77542       	12944       	5546        	724         
```
######MOVES (EXCHANGES)
```
RANDOMIZED INPUT
           	size = 5000	  size = 1000	  size = 500	  size = 100	
      Heap	6148        	1153        	621         	127         	
 Insertion	5065490     	156167      	52885       	1931        	
     Merge	123616      	19952       	8976        	1344        	
     Quick	5142        	999         	499         	99          	
 Selection	5000        	1000        	500         	100         	
     Shell	38771       	6472        	2773        	362         	

REVERSED INPUT
           	size = 5000	  size = 1000	  size = 500	  size = 100
      Heap	8991        	1497        	891         	189         	
 Insertion	6758632     	210132      	68440       	2943        	
     Merge	123616      	19952       	8976        	1344        	
     Quick	4999        	999         	499         	99          	
 Selection	5000        	1000        	500         	100         	
     Shell	38771       	6472        	2773        	362         
     
SORTED INPUT     
Duration
           	size = 5000	  size = 1000	  size = 500	  size = 100
      Heap	6834        	998         	676         	117         	
 Insertion	2461117     	16190       	24939       	601         	
     Merge	123616      	19952       	8976        	1344        	
     Quick	4999        	999         	499         	99          	
 Selection	5000        	1000        	500         	100         	
     Shell	38771       	6472        	2773        	362      
```
###### DUPLICATED WORDS
```
TOTAL SIZE: 100 WORDS
UNIQUE WORDS: 5 (5%)
Duration
           	size = 100	
      Heap	3.2423e-05  	
 Insertion	8.187e-06   	
     Merge	0.000226893 	
     Quick	4.3137e-05  	
 Selection	0.000145944 	
     Shell	1.7498e-05  	

Compares
           	size = 100	
      Heap	96          	
 Insertion	376         	
     Merge	763         	
     Quick	1421        	
 Selection	4952        	
     Shell	724         	

Moves (exchanges)
           	size = 100	
      Heap	614         	
 Insertion	188         	
     Merge	1344        	
     Quick	340         	
 Selection	100         	
     Shell	362         	    

TOTAL SIZE: 1000 WORDS
UNIQUE WORDS: 450 (45%)
Duration
           	size =    1000	size =    500	size =    100	
      Heap	0.000479613 	0.000215011 	3.2388e-05  	
 Insertion	0.00379864  	1.966e-05   	5.022e-06   	
     Merge	0.0143818   	0.00722617  	0.00137771  	
     Quick	0.00378812  	0.000209361 	4.0284e-05  	
 Selection	0.0135738   	0.00357404  	0.000144242 	
     Shell	0.000184221 	8.5859e-05  	1.9449e-05  	

Compares
           	size =    1000	size =    500	size =    100	
      Heap	1972        	4           	0           	
 Insertion	248862      	998         	198         	
     Merge	12162       	4974        	672         	
     Quick	356025      	7319        	1075        	
 Selection	499502      	124752      	4952        	
     Shell	12944       	5546        	724         	

Moves (exchanges)
           	size =    1000	size =    500	size =    100	
      Heap	8972        	4471        	661         	
 Insertion	124431      	499         	99          	
     Merge	19952       	8976        	1344        	
     Quick	2772        	2270        	356         	
 Selection	1000        	500         	100         	
     Shell	6472        	2773        	362         	
