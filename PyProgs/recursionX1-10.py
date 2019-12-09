
# Author Francis Adepoju, G00364694. December 1 - 10, 2019
# Strictly PYTHON  3.7.4
# ACKNOWLEDGEMENT:
    # Most of the ideas used in this work were adapted from https://stackoverflow.com/questions

def pow(num, power):
    """
    The function raises the provided number to the power supplied. 
    This is peformed by the use of recursion. This method has no side effects.
    """
    # This is the base case for recursion as 
    # Any number to the power of 1 is itself i.e. 2^1 = 2
    if (power == 1):
        return num
    elif power == 0:
        return 1
    # Here we perform recursion by invoking our method
    # with a lesser power thereby reducing the work and moving toward the base case as 2^3 = 2 * (2^2)
    return num * pow(num, power-1)

def sumUp(word):
    """
    Q1 ...Sum of an array ..Given an array of numbers return it's sum (all the numbers added together).
    This function takes in an array of numbers and then returns the sum of the numbers using recurssive method 
    Assuming there are at least 2 elements in the array. This method has no side effects.
    
    INPUT:  Array of integers.
    OUTPUT: Sum totalof the elements in the input array
    """
    # Compute the length of the current input array
    length = len(word)
    #print("length was %d - " % length)
    # This is the base case. The recurssion will end if the array has less than one elements.
    if (length <= 1):
        return word[0]
    #print( "comparing %s with %s result is %r" % (word[0], word[length-1], (word[0] == word[length-1])))
    #print(word)
    # print(word[0])
    # Here we perform recursion by invoking the function with reduced array element and summing with previous result of addition
    # starting with the first element in the array
    return (word[0] + sumUp(word[1:length]))

def muxUp(word):
    """
    Q2 ...Product of an array Given an array of numbers return it's product (all the numbers multiplied together).
    This function takes in an array of integers and returns a multiplication of the array elements. 
    This is peformed by the use of recursion. This method has no side effects.
    
    INPUT:  Array of integers.
    OUTPUT: Sum totalof the elements in the input array 
    """
    # Compute the length of the current input array
    length = len(word)
    #print("length was %d - " % length)
    
    # This is the base case. The recurssion will end if the array has less than one elements.
    if (length <= 1 ):
        return word[length-1]
    #print( "comparing %s with %s result is %r" % (word[0], word[length-1], (word[0] == word[length-1])))
    
    # Here we perform recursion by invoking the function with reduced array element and multiplying with previous result of addition
    # starting with the first element in the array
    return (word[0] * muxUp(word[1:length]))

def removeODD(word):
    """
    Q3 ...Remove all odd numbers Given an array of numbers return an array with all the odd numbers removed.
    This function takes in an array of integers and returns only the EVEN number elements in the array. 
    It rejects the ODD number elements, in essence. 
    This is peformed by the use of recursion. This method has no side effects.
    
    INPUT:  Array of any mix of even and odd integers.
    OUTPUT: Retun only the odd numbers in the input array 
    """
    # This is the base case. The recurssion will end if the array has less than no elements or all elements has been processed.
    if not word:
        return []

    # Here we perform recursion by invoking the function with reduced array element and checking for the test condition
    # The current element is admitted into the the returned array only if it is EVEN
    # starting with the first element in the array   
    if word[0] % 2 == 0:
        return [word[0]] + removeODD(word[1:])
    return removeODD(word[1:])    
        
def removeEven(word):
    """
    Q4 ...Remove all even numbers Given an array of numbers return an array with all the even numbers removed.
    This function takes in an array of integers and returns only the ODD number elements in the array. 
    It rejects the EVEN number elements, in essence. 
    This is peformed by the use of recursion. This method has no side effects.
    
    INPUT:  Array of any mix of even and odd integers.
    OUTPUT: Retun only the even numbers in the input array 
    """
    # This is the base case. The recurssion will end if the array has less than no elements or all elements has been processed.
    if not word:
        return []
    # Here we perform recursion by invoking the function with reduced array element and checking for the test condition
    # The current element is admitted into the the returned array only if it is ODD
    # starting with the first element in the array

    if word[0] % 2 != 0:
        return [word[0]] + removeEven(word[1:])
    return removeEven(word[1:])    

def changeCharacter(word,oldchar):
    """
    Q5 ...Replace a given character with '*' Given a string, and a character to replace,
    return a string where each occurance of the character is replaced with '*'.
    This function takes in a string input and returns only a new instance of the string with the specified 
    character replaced with a '*'. This is peformed by the use of recursion. This method has no side effects.
    
    INPUT:  A string input and a character to replace with *
    OUTPUT: Retun the transformed string 
    """
    newchar = '*'

    # This is the base case. The recurssion will end if the input string has no more elements in it.
    if word == '':
        return ''
    
    #   NOTE: This is easily done with the in-buit function... return word.replace(character,'*')
    #  We first convert the input character (oldchar) to lowercase before proceeding with the recurssive treatment of next element
    if word[0].lower() == oldchar.lower():
        return newchar + changeCharacter(word[1:], oldchar)
    return word[0] + changeCharacter(word[1:], oldchar)   

def recursiveIndex(Lst, val, index=0):
    """
    Q6 ...Find index in array for item. Given an array, and an element to search for return
    the index of the element in the array or -1 if the element is not present in the array.
    This function takes in an array of items and returns the index of the element if present
    It returns a -1 if element is not present in the array. This is peformed by the use of recursion. 
    This method has no side effects.
    
    INPUT:  Array of any mix, the member whose index is to be returned if present in the array.
    OUTPUT: Retun index of array element if present or -1 if not present in the array 
    """
    length = len(Lst)
    # This is the base case. The recurssion will end if the input string has no more elements in it.
    if length == 0:
        return ''

    # Here we recurssively go over the array list. 
    # If element is not found, an exception is forked to return a -1
    try:
        if Lst[index] == val:
            return index 
        # else:
    # try:
            # return 1 + recursiveIndex(Lst[1:], val)
    except IndexError:
        return -1
    return recursiveIndex(Lst, val, index+1)

def sumDigits(n):
    """
    Q7 ...Sum of Digits Given a whole number such as 23, return the sum of the digits in the
    number i.e. 2 + 3 = 5. 
    This function takes in a number and then sums up the digits in the number. This is peformed by the use of recursion. 
    This method has no side effects.
    
    INPUT:  A number (Integer).
    OUTPUT: Retun the sum of the digits in the number 
    """
    # This is the base case. The recurssion will end if there in no digit greater than 10 in the input.
    if n < 10:
        return n
    else:
        # PYTHON 3 - recursively separate the digits until it is less than 10 and then sum them up recursively
        allDigits = n // 10 
        lastDigit = n % 10
        return sumDigits(allDigits) + lastDigit

def printArrRecursively(arr):
    """
    # Q8 ...Print an array Given an array of integers prints all the elements one per line. This
    is a little bit diferent as there is no need for a 'return' statement just to print and recurse.
    This function takes in an array of integer and pring the elements out one per line recurssively. 
    This method has no side effects.
    
    INPUT:  An array of Integer.
    OUTPUT: Each array element prints on a new line. 
    """
    # This is the base case. The recurssion will end if there in no element left in the array input.
    if len(arr) == 0:
        print("Array is now Empty...")
    
    if len(arr) != 0:
        print(arr[0])
        printArrRecursively(arr[1:])

def minimum(lst):
    """
    Q9 ...Find the minimum element in an array of integers. 
    You can carry some extra information through method arguments such as minimum value.
    This is just one way of how to iterate through a list using recursion in Python. 
    The approach is to continuously split the list into halves until you get a list of length 1, 
    At that stage, the minimum element would have been found.
    This method has no side effects.
    
    INPUT:  An array of Integer.
    OUTPUT: PRint the minimum of elements in the input array. 
    """
    # This is the base case. The recurssion will end if there in no element left in the array input.
    if len(lst) == 0:
        return 'Empty'

    if len(lst) == 1:
        return lst[0]
    else:
        m1 = minimum(lst[0:int(len(lst) / 2)])
        m2 = minimum(lst[int(len(lst) / 2):])
        if m1 < m2:
            return m1
        else:
            return m2

def closeParenthesis(s, i=0, cnt=0):
    '''
    Q10 ...Verify the parentheses Given a string, return true if it is a nesting of zero or more
    pairs of parenthesis, like \(())" or \((()))"
    The LOGIC: when you find an open parenthesis, call the function. 
    when the function finds a close parenthesis, return. If the function finds the end of string, there's an open 
    and no close parenthesis. If the top function returns and a close parenthesis is found later in the string, 
    there's an unmatched close parenthesis. This method has no side effects.
    
    INPUT:  An arbitrary string of open and close parenthesis with nothing inside them.
    OUTPUT: Print TRUE if patenthesis is fully closed or FALSE otherwise. 
    '''
    # This is the base case. The recurssion will end if there in no element left in the input string.
    if i == len(s): 
        return cnt == 0
    
    if cnt < 0: 
        return False

    if s[i] == "(": 
        return  closeParenthesis(s, i + 1, cnt + 1)
    elif s[i] == ")": 
        return  closeParenthesis(s, i + 1, cnt - 1)
    return closeParenthesis(s, i + 1, cnt)

# END of functions

if __name__ == "__main__":
    # Run the functions one after the other as detailed below...
    print("===================================== Q0.==========================================")
    # Test the Power function
    print("Running the power function")
    print("3^4 = ", pow(3,4))
    print("6^6 = ", pow(6,6))
    print("0^4 = ", pow(0,4))
    print("6^0 = ", pow(6,0))
    print("===================================== Q1.==========================================")
    
    # Test the sunUp() function
    print("Summing up array elements")    
    num1 = [10, 20, 45, 9, 5,10,900]
    num2 = [9,9]
    num3 = [99]
    print("[10, 20, 45, 9, 5,10,900] = ", sumUp(num1))
    print("                    [9,9] = ", sumUp(num2))
    print("                     [99] = ", sumUp(num3))
    print("===================================== Q2.==========================================")

    # Test the muxUp() function
    num11  = [10, 2, 9, 5, 0.5]
    num12  = [9]
    num13 = [0,30,1000]  #first element = 0
    print("Multiplying up array elements")
    print("[10, 2, 9, 5, 0.5] = ", muxUp(num11))
    print("               [9] = ", muxUp(num12))
    print("       [0,30,1000] = ", muxUp(num13))
    print("===================================== Q3.==========================================")

    # Test the removeODD() function
    num111 = [10, 12, 9, 2, 24, 25, 11, 3, 33, 98, 100, 111, 120]
    num112 = [9]
    num113 = [0, 11, 8, 13]
    print("Return All the Even numbers in this array - [10, 12, 9, 2, 24, 25, 11, 3, 33, 98, 100, 111, 120]\n", removeODD(num111))
    print("Return All the Even numbers in this array - [9]\n", removeODD(num112))
    print("Return All the Even numbers in this array - [0,11,8,13]\n", removeODD(num113))
    print("===================================== Q4.==========================================")
   
    # Test the removeEVEN() function
    num121 = [10, 12, 9, 2, 24, 25, 11, 3, 33, 98, 100, 111, 120]
    num122 = [9]
    num123 = [0, 11, 8, 13]
    print("Return All the Odd numbers in this array - [10, 12, 9, 2, 24, 25, 11, 3, 33, 98, 100, 111, 120]\n", removeEven(num121))
    print("Return All the Odd numbers in this array - [9]\n", removeEven(num122))
    print("Return All the Odd numbers in this array - [0,11,8,13]\n", removeEven(num123))
    print("===================================== Q5.==========================================")
    
    # Test the changeCharacter() function
    st = 'Miss. Lissanalta Stepph'
    print("     s in 'Miss. Lissanalta Stepph'==>", changeCharacter(st, 's'))
    print("     . in 'Miss. Lissanalta Stepph'==>", changeCharacter(st, '.'))
    print("     a in 'Miss. Lissanalta Stepph'==>", changeCharacter(st, 'a'))
    print("     l in 'Miss. Lissanalta Stepph'==>", changeCharacter(st, 'l'))
    print(" blank in 'Miss. Lissanalta Stepph'==>", changeCharacter(st, ' '))
    print("===================================== Q6.==========================================")
    
    # Test the recursiveIndex() function
    numA = [10, 12, 9, 2, 24, 25, 11, 3,'Q', 33, 98, 100, 111, 120]
    print("Input array ==> ",numA)
    print("Index of 111 in array      ==> ", recursiveIndex(numA, 111))
    print("Index of  10 in array      ==> ", recursiveIndex(numA, 10))
    print("Index of   2 in array      ==> ", recursiveIndex(numA, 2))
    print("Index of  11 in array      ==> ", recursiveIndex(numA, 11))
    print("Index of 'Q' in array      ==> ", recursiveIndex(numA, 'Q'))
    print("Index of  98 in array      ==> ", recursiveIndex(numA, 98))
    print("Index of 599 in array      ==> ", recursiveIndex(numA, 599))
    print("Index of  33 in array      ==> ", recursiveIndex(numA, 33))
    print("===================================== Q7.==========================================")
    
    # Test the sumDigits() function
    print("Summing the digits in     7 ==>", sumDigits(7)) 
    print("Summing the digits in   509 ==>",sumDigits(509))
    print("Summing the digits in   109 ==>",sumDigits(109))
    print("Summing the digits in    11 ==>",sumDigits(11))
    print("Summing the digits in    43 ==>",sumDigits(43))
    print("Summing the digits in    15 ==>",sumDigits(15))
    print("Summing the digits in 25991 ==>",sumDigits(25991))
    print("===================================== Q8.==========================================")
    
    # Test the printArrRecursively() function
    arrayItems1 = [66, 0, 91, 3, 55, 8, 18, 81, 200, 111]
    arrayItems2 = []
    arrayItems3 = arrayItems1 * 2
    print("arrayItems1: ", arrayItems1)
    printArrRecursively(arrayItems1)
    print("arrayItems2: ", arrayItems2)
    printArrRecursively(arrayItems2)
    print("arrayItems3: ", arrayItems3)
    printArrRecursively(arrayItems3)

    print("===================================== Q9.==========================================")
    # Test the minimum() function
    arrayItems1 = [66,0,91,3,55,8,18,81,-200,111,-789]
    arrayItems2 = [66,10,91,23,55,18,18,81,1200,111,9.99]
    arrayItems3 = [66,0,91,3,55,8,18,81,200,111,13,67,22]
    arrayItems4 = [66,0,91,-3,55,8,18,81,250,111]
    arrayItems5 = [5]
    arrayItems0 = []

    print("                                     Minimum item in [] is: ", minimum(arrayItems0))
    print("   Minimum item in [66,0,91,3,55,8,18,81,-200,111,-789] is: ", minimum(arrayItems1))
    print("Minimum item in [66,10,91,23,55,18,18,81,1200,111,9.99] is: ", minimum(arrayItems2))
    print("Minimum item in [66,0,91,3,55,8,18,81,200,111,13,67,22] is: ", minimum(arrayItems3))
    print("        Minimum item in [66,0,91,-3,55,8,18,81,250,111] is: ", minimum(arrayItems4))
    print("                                    Minimum item in [5] is: ", minimum(arrayItems5))

    print("===================================== Q 10.==========================================")
    # Test the closeParenthesis() function
    # Showing off the rep() string (!r) capability to display a quoted string as well...
    s1 = "((()))())"
    s2 = ")()("
    s3 = "()()"
    s4 = "(())"
    s5 = "(()"
    s6 = ")"
    s7 = "("
    s8 = "((((()))))"
    s9 = "((((()(((("
    print("{!r} ==> {}".format(s1, closeParenthesis(s1)))
    print("{!r} ==> {}".format(s2, closeParenthesis(s2)))
    print("{!r} ==> {}".format(s3, closeParenthesis(s3)))
    print("{!r} ==> {}".format(s4, closeParenthesis(s4)))
    print("{!r} ==> {}".format(s5, closeParenthesis(s5)))
    print("{!r} ==> {}".format(s6, closeParenthesis(s6)))
    print("{!r} ==> {}".format(s7, closeParenthesis(s7)))
    print("{!r} ==> {}".format(s8, closeParenthesis(s8)))
    print("{!r} ==> {}".format(s9, closeParenthesis(s9)))
    print("===================================== END ===========================================")