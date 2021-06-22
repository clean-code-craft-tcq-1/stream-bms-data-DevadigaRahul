#-------------------------------------------------------------------------------------------
#Includes 
#-------------------------------------------------------------------------------------------
import wrapper #use for Mocking 

#-------------------------------------------------------------------------------------------
#Functions 
#-------------------------------------------------------------------------------------------

#Generates random BMS reading
def generate_random_reading(BMS_attribute_range):
    reading={}
    wrapper.random_float.count=0
    for attribute in BMS_attribute_range:
        reading[attribute] = round(wrapper.random_float(BMS_attribute_range[attribute]['min'],BMS_attribute_range[attribute]['max']+1),2)#wrapper:random_float->random.uniform
    return reading

    
#Streaming readings  
def stream_readings(length,time_out,BMS_attribute_range):#length:No stream;time_out:Time out between each each stream
    wrapper.stream.count=0#Clearing wrapper counter for delay->time.sleep 
    wrapper.delay.count=0#Clearing wrapper counter for stream->print
    if bool(BMS_attribute_range):#Check if dictionary is empty
        for x in range(0,length):
            wrapper.stream(generate_random_reading(BMS_attribute_range))#wrapper:stream->print
            wrapper.delay(time_out)#wrapper:stream->time.sleep


#-------------------------------------------------------------------------------------------
#Main  
#-------------------------------------------------------------------------------------------              
if __name__ == '__main__':
    #BMS attribute with Range
    BMS_attribute_range ={
    'temp':{'min':1,'max':45},#Temperature in Celesius
    'soc':{'min':20,'max':80},#state of Charge
    }
    stream_readings(15,2,BMS_attribute_range)





