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
* FILENAME : procPcap.h
*
* DESCRIPTION :
*       .h file for procPcap.c.
* 
* AUTHOR :  Jarrod N. Bakker    START DATE :    2/11/2016
*
**/
#ifndef PROCPCAP_H
#define PROCPCAP_H

int ppEthDst(char *inputPCAP, const unsigned char *newMAC, char *outputPCAP);

#endif
