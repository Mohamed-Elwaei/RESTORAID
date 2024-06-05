# RESTORAID
Checks if data can be restored with the disks given.


Given the raid level T, number of disks N, the chunk size C, the stripe number S, and the number of working disks W. This program checks if data dumped can be restored. If it can it prints them in the form of a string, and otherwise prints 'data lost'. Each sector in this scenario contains a single byte. 

The first input line is T, N, C, S, and W.
The second line is the W sectors that are working (0-indexed).

The following S lines contain W characters. The character stored in each disk and stripe.

