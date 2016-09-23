l*******************************************************************************
************************************* RESIZE METHOD ****************************
The resize method first checks to see if the memory postion to free exists and if it does then we store the size of the memory block that we want to resize. Next we check to see if the old size if >= to the new requested size and if so we are unable to resize it to a smaller size so we return the original block that was passed in as a parameter. If all passes then we find the memory block to the right of the block that we are trying to resize, if that block does exist then we make a parameter called combinedSized that is the sum of the old size plus the sum of the next size plus 16(16 for the sizeOfPrefix+sizeOfSuffix). Next we compare combinedSizes with newSize and if it is greater than or equal then we update current by adding the current block to the right block in a method called "combine". Next if there is extra space after combining the two then we split the block and make one block of the "newSize" and the other is the remainder.
********************************************************************************

********************************************************************************
************************** BEST FIT METHOD *************************************
This method is identical to "firstFitAllocRegion" except for at line 385 where instead of calling "p = findFirstFit(s);"  we call "p = findBestFit(s);"  this is the actual method that finds the best spot. It has initial parameters that are visible to the entire method call to help keep track of the which memory block we are currently at and the best size difference. We start the best size different to a parameter called "currentBestSizeDifference" and initialize it to negative that we can know if it has found its first spot(regardless if it is the best spot). Then we start traversing the memory block from the start of the head and as we traverse if we find a spot that is unallocated then we make a parameter called "justFoundSizeDifference" which is the difference of the currently traversed spot minus the best size that we are trying to find. The first the we check is if the difference is zero, if so we return the currently traversed memory block. Else if it is the first found possible spot(we know this because "currentBestSizeDifference" is a negative value) we change the currentBestSizeDifference to justFoundSizeDifference. Then we repeat the process after each iteration. If we dont find an exact spot then we exit the while loop and if the we never found a valid spot(know this because "currentBestSizeDifference" still has a negative value) we return " growArena(s);"  or the best available spot "currentBestFit"
********************************************************************************
************************* TEST CASES FOR RESIZE  *******************************
				       
All the test cases I conducted were with a .c file called "myTestCases.c"... First i created sizes 16 allotments of memory each of size 8 less than thre previous one. Then i called free on key spots [2,4,6,7,8,10,16,15,14]
    
1)checked resize(p1,X) where x is the size of p1+p2+16+1
   .it will NOT resize because to big
2)checked resize(p1,X) where x is the size of p1+p2+16
   .it WILL resize but not create new block
3)checked resize(p1,X) where x is the size of p1+p2
   .it WILL resize but not create new block because needs extra space for new block plus 16
4)checked resize(p1,X) where x is the size of p1+p2-16
   .it WILL resize and WILL create new block because needs extra space for new block plus 16


********************************************************************************
************************* TEST CASES FOR BEST FIT ******************************
By this point every other block of memory is free and and in acending order, smallest free slot first and largest last.....

1)Do bestFitAllocRegion of size larger than the last slot(with biggest space available)
     does not add a new block, and does not make the arena size grow
2)Do bestFitAllocRegion of size 1
     takes the first spot(since is the one with smallest space)
3)Do bestFitAllocRegion with a size bigger than the first(smallest) and smaller than the last(largest) block
     fits it a free block between largest and smallest.
