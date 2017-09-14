# PCAP_ETHD
A program for changing the destination MAC address of packets within a PCAP file. Broadcast MAC addresses are left unchanged.

Note:
1. This program requires **libpcap-dev** to be installed.
2. Is built using **make**.

Usage of the resulting program is as follows:
```bash
$ ethd <MAC address> <input PCAP> <output PCAP>
```
