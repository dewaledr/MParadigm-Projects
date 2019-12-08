
'''
Recursive solutions to the following: Nov, 2019
1. Calculate powers e.g. power(3,3), where that would be 3 * 3 * 3
2. Determine if a word is a palindrome, this means the same backwards
    as forwards e.g. poop, madam...
3. Reverse a String, i.e. given dominic return cinimod.
'''
def pow(num, power):
    if (power == 1):
        return num
    return num * pow(num, power-1)
    
def palindrome1(word):
    length = len(word)
    #print("length was %d" % length)
    if (length <= 1):
        return True
    #print( "comparing %s with %s result is %r" % (word[0], word[length-1], (word[0] == word[length-1])))
    return (word[0] == word[length-1]) and palindrome1(word[1:length-1])
    
def reverse(word):
    length = len(word)
    if (length <= 1):
        return word
    return word[length-1] + reverse(word[:length-1])

print(palindrome1("dood"))
print(palindrome1("madam"))
print(palindrome1("cinimod"))

print(reverse("cinimod"))
print(reverse("GMIT"))


''' Palidrome'''
def palidrome(stg):
    stg = stg.replace(' ','') #This will replace all spaces with no space
                              # Fixes issues with strings that have spaces +
                              # without using regular expression to do it.
    # Will return True if str == str[::-1]
    print(f"{stg} - {stg[::-1]}")
    return stg == stg[::-1]


def pal2(stg):
    stg = stg.replace(' ','')
    #str = [stg]
    #n = len(str2)
    #print(stg)
    newStr = ''
    if (len(stg) == 0):
        return 'Empty String'
    
    #newStr.replace          .clear()
    newStr = stg[:-1]
    # str2.pop(-1)
    #str = str[-1]
    #del str[-1]
    #print(newStr)
    ##return 'done'
    if (len(newStr) == 0):  
        return pal2(newStr) == stg[::-1]
    else:
        return 'Not a Palidrome'

# Check it out
print(palidrome('poop'))
print(palidrome('nurses run'))
print(palidrome('madam'))
print(palidrome('abcba'))
print(palidrome('rhetoric'))

print(pal2('poop'))
print(pal2('nurses run'))
print(pal2('madam'))
print(pal2('abcba'))
print(pal2(''))
print(pal2('rhetoric'))



# def finder_rec(data, x):
#     '''
#     Finder_rec is a function that goes over an input array in order 
#     to determine the largest member of the array
#     '''
#     # Base case...Stops when no more member in the array
#     if x == 0:
#         return data[x]
#     #Otherwise
#     # Set variable v1 to the (size of the input data - 1)
#     # Because arrays are zero indexed...
    
#     # Initially, set v1 to the last member of the input data set
#     v1 = data[x]
#     # Recursively Pass data and the data-index penultimate to the 
#     # current index into finder_rec() and compare until x == 0
#     # At the end (x == 0) the largest input member is returned

#     v2 = finder_rec(data, x-1)
#     if v1 > v2:
#         return v1
#     else:
#         return v2

# # Test data input
# inData = [0, -247, 341, 1001, 741, 22]
# print(finder(inData))


# def finder2(data):
#     '''
#      Finder is an alternate function that goes over an input array in order 
#      to determine the largest member of the array. In this implementation, we sort the array 
#      and return the last item - which is naturally the biggest.
#      '''
#     # Total length of input (array)
#     print(f'{len(data)-1}')
#     # Sort the array in-place and return the last item
#     return sorted(data)[len(data)-1]

# # Test data input
# inData = [0, -247, 341, 1001, 741, 22]
# print(finder2(inData))