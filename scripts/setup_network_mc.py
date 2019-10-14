#!/usr/bin/env python
import subprocess
import sys

# first, determine which mini-cheetah we are

mc_id = -1

try:
    with open('/home/user/mc_id') as f:
        mc_id = int(f.read().split()[0])
except:
    sys.exit("Mini cheetah number is not set.")

print("Setup for mini cheetah {}".format(mc_id))

# next, array of network adapters
adapter_names = { 1 : "enxa0cec8ca8e63" }


if mc_id in adapter_names.keys():
    adapter_name = adapter_names[mc_id]
    print("adapter is {}".format(adapter_name))
    subprocess.call(['sudo', 'ifconfig', adapter_name, 'multicast'])
    subprocess.call(['sudo', 'route', 'add', '-net', '224.0.0.0', 'netmask', '240.0.0.0', 'dev', adapter_name])
else:
    print("No adpater for this mini cheetah ID, add it in setup_network_mc.py")


