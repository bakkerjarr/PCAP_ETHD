# PCAP_ETHD
A program for changing the destination MAC address of packets within a PCAP file. Broadcast MAC addresses are left unchanged.

Note that this program requires libpcap-dev to be installed.

Usage of the resulting program is as follows:
```bash
$ ethd <MAC address> <input PCAP> <output PCAP>
```
