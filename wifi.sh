#! /bin/bash

ifconfig wlan0
iwconfig wlan0 essid Nunes key s:55467B2352
dhclient wlan0
