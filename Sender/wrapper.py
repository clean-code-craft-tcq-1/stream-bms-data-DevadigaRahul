#This file is used for Mocking->counting the occurence of called buit-in function[Wrapper]

import random
import time

class wrapper:#Decorator
    #wraps a function, to keep a running count of how many
    #times it's been called
    def __init__(self, func):
        self.func = func
        self.count = 0

    def __call__(self, *args, **kwargs):
        self.count += 1
        return self.func(*args, **kwargs)

#-------------------------------------------------------------------------------------------
#Wrapping bulit in function 
#-------------------------------------------------------------------------------------------
stream = wrapper(print)#wrapper:stream->print
delay = wrapper(time.sleep)#wrapper:stream->time.sleep
random_float = wrapper(random.uniform)#wrapper:Remove->dict.pop

