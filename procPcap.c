/*************************************************************************
* Copyright 2017 Jarrod N. Bakker
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* FILENAME : procPcap.c
*
* DESCRIPTION :
*       This file uses XML data to filter PCAP data into a new PCAP file.
* 
* AUTHOR :  Jarrod N. Bakker    START DATE :    2/11/2016
*
**/

#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <netinet/if_ether.h> // The Ethernet frame header
#include "procPcap.h"

static void processPkt(const unsigned char *rawPkt,
                       const struct pcap_pkthdr *rawHdr,
                       const unsigned char *newMAC);

static const unsigned char BROADCAST_MAC[6] = {0xff, 0xff,0xff,0xff,0xff,0xff};

/**
 * Changes the destination MAC address of packets within the PCAP
 * file 'inputPCAP' to 'newMAC' if the original is not the broadcast
 * MAC address. The modified packets are writen to the new PCAP file
 * 'outputPCAP'.
 * 
 * param inputPCAP: Path of the input PCAP file.
 * param newMAC: MAC address to write in.
 * param outputPCAP: Path of the new PCAP file.
 * return: 1 if successful, 0 otherwise.
 */
int ppEthDst(char *inputPCAP, const unsigned char *newMAC, char *outputPCAP){
    char errbuf[PCAP_ERRBUF_SIZE];
    fprintf(stdout,"Opening PCAP data using file: %s\n", inputPCAP);
    pcap_t *pcapIn = pcap_open_offline(inputPCAP, errbuf);
    if (pcapIn == NULL) {
        fprintf(stderr, "ERROR: PCAP error: %s\n", errbuf);
        return 0;
    }
    fprintf(stdout,"Opening output PCAP data using file: %s\n", outputPCAP);
    pcap_t *pcapFormat = pcap_open_dead(DLT_EN10MB, 65535);
    pcap_dumper_t * pcapOut = pcap_dump_open(pcapFormat, outputPCAP);
    
    const unsigned char *pkt;
    struct pcap_pkthdr *header;
    int i = 0;
    int times = 100000;
    while ((pkt = pcap_next(pcapIn, header)) != NULL) {
        /* Replace the destination MAC address if needed. */
        processPkt(pkt, header, newMAC);
        /* Write the packet to the new PCAP file. */
        pcap_dump(pcapOut, header, pkt);
        /* Output a message to stdout every now and then. */
        ++i;
        if (i%times == 0)
            fprintf(stdout, "\tProcessed %d packets.\n", i);
    }
    /* Close PCAP files etc */
    pcap_close(pcapIn);
    pcap_dump_close(pcapOut);
    pcap_close(pcapFormat);
    return 1;   
}

/**
 * Replace the destination MAC address of a packet with newMAC if 
 * the current destination MAC address is no the broadcast MAC address.
 * 
 * Assumes that the packet uses Ethernet encapsulation.
 * 
 * param rawPkt: The packet to process.
 * param rawHdr: PCAP header of the packet.
 * param newMAC: MAC to overwrite with.
 */
static void processPkt(const unsigned char *rawPkt, 
                       const struct pcap_pkthdr *rawHdr,
                       const unsigned char *newMAC){
    const unsigned char *pkt = rawPkt;
    struct pcap_pkthdr *hdr = rawHdr;
    /* The packet should be larger than the Ethernet header. */
    if (hdr->caplen < sizeof(struct ether_header)){
        return;
    }    
    const struct ether_header *eth = (struct ether_header*) pkt;
    /* Replace the destination MAC address if needed */
    const unsigned char *dmac = eth->ether_dhost;
    if (strcmp(dmac, BROADCAST_MAC) != 0){
        strcpy(dmac, newMAC);
    }
}
