## Description

Implementation of a parameterizable average access time calculator.

Where _acesso \ _l1_ is the time in ns to access the first level and _t \ _miss \ _l1_ is the failure rate of the first level (in accesses per 100,000). Similarly, there are parameters for the second and third level of _caches_ as well as for the main memory access time.

If the access time of a level is set to _zero_, the level (and all levels below with the exception of memory) are ignored.

The function returns the average access time calculated in ns. The final value should be rounded up if necessary.