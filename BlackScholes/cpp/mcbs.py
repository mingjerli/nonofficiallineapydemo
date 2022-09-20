import ctypes
import sys
import os 

dir_path = os.path.dirname(os.path.realpath(__file__))
handle = ctypes.CDLL(dir_path + "/libTest.so")     

handle.My_mc_call.argtypes = [ctypes.c_int, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double] 
handle.My_mc_call.restype = ctypes.c_double
def call(num_sims, S, K, r, v, T):
    result = handle.My_mc_call(num_sims, S, K, r, v, T)
    print(result)
    return result

handle.My_mc_put.argtypes = [ctypes.c_int, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double] 
handle.My_mc_put.restype = ctypes.c_double
def put(num_sims, S, K, r, v, T):
    result = handle.My_mc_put(num_sims, S, K, r, v, T)
    print(result)
    return result    