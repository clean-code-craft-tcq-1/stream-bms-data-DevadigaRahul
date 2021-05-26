import unittest
import Sender


class SenderTest(unittest.TestCase):
  #Test for generate_random_reading 
  def test_for_not_generate_random_reading(self):#Negative senario when there is no BMS attribute and range
    self.assertFalse(bool(Sender.generate_random_reading({})))#Returns empty reading
    self.assertTrue(Sender.wrapper.random_float.count==0)#Checking random_float->random.uniform is called zero times 
    

  def test_for_generate_random_reading_for_one_BMS_attribute(self):#Negative senario when there is no BMS attribute and range
    BMS_attribute_range ={
    'temp':{'min':1,'max':45},#Temperature in Celesius
    }
    self.assertTrue(bool(Sender.generate_random_reading(BMS_attribute_range)))#Returns  non-empty reading
    self.assertTrue(Sender.wrapper.random_float.count==1)#Checking random_float->random.uniform is called one times 
    
    
  #Test for streaming reading
  def test_for_empty_BMS_attribute_range(self):#Negative senario when there is no BMS attribute and range
    BMS_attribute_range ={}#Invalid Input->Empty dict BMS attribute
    Sender.stream_readings(1,1,BMS_attribute_range)
    self.assertTrue(Sender.wrapper.delay.count==0)#Checking delay->time.sleep is called zero times 
    self.assertTrue(Sender.wrapper.stream.count==0)#Checking stream->print is called zero times
    
  def test_for_not_streaming_any_readings(self):#min
    BMS_attribute_range ={
    'temp':{'min':1,'max':45},#Temperature in Celesius
    }
    Sender.stream_readings(0,0,BMS_attribute_range)
    self.assertTrue(Sender.wrapper.delay.count==0)#Checking delay->time.sleep is called zero times 
    self.assertTrue(Sender.wrapper.stream.count==0)#Checking stream->print is called zero times

  def test_for_streaming_one_reading(self):#min+1
    BMS_attribute_range ={
    'temp':{'min':1,'max':45},#Temperature in Celesius
    'soc':{'min':20,'max':80},#state of Charge
    }
    Sender.stream_readings(1,1,BMS_attribute_range)
    self.assertTrue(Sender.wrapper.delay.count==1)#Checking delay->time.sleep is called one times 
    self.assertTrue(Sender.wrapper.stream.count==1)#Checking stream->print is called five times
    
  def test_for_streaming_more_then_one_reading(self):#min+2 ,since max is not defined
    BMS_attribute_range ={
    'temp':{'min':1,'max':45},#Temperature in Celesius
    'soc':{'min':20,'max':80},#state of Charge
    'charge_rate':{'min':0,'max':0.8},#state of Charge
    }
    Sender.stream_readings(2,2,BMS_attribute_range)
    self.assertTrue(Sender.wrapper.delay.count==2)#Checking delay->time.sleep is called two times 
    self.assertTrue(Sender.wrapper.stream.count==2)#Checking stream->print is called two times 
    
if __name__ == '__main__':
  unittest.main()
