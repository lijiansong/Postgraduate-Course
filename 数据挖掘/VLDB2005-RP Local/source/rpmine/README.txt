Mining Compressed Frequent-Pattern Set

Author: Dong Xin, University of Illinois at Urbana-Champaign

The program is built upon FPClose source code, 
"PEfficiently Using Prefix-trees in Mining Frequent Itemsets" 
Gosta Grahne and Jianfei Zhu,
{FIMI'03} Workshop on Frequent Itemset Mining Implementations.
http://www.cs.concordia.ca/db/dbdm/dm.html

////////////////////////////////////////////////////////////////
Original Copyright:

Copyright (c) 2003, Concordia University, Montreal, Canada
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions 
are met:
   - Any use of the software must be for non-commercial educational 
     or research purposes. 
   - Redistributions of source code must retain the above copyright 
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright 
     notice, this list of conditions and the following disclaimer in 
     the documentation and/or other materials provided with the 
     distribution.
   - Neither the name of Concordia University nor the names of its 
     contributors may be used to endorse or promote products derived 
     from this software without specific prior written permission

This software is provided by the copyright holders and contributors 
"AS IS" and any express or implied warranties, including, but not 
limited to, the implied warranties of merchantability and fitness for 
a particular purpose are disclaimed. In no event shall the copyright 
owner or contributors be liable for any direct, indirect, incidental, 
special, exemplary, or consequential damages (including, but not limited 
to, procurement of substitute goods or services; loss of use, data, or 
profits; or business interruption) however caused and on any theory of 
liability, whether in contract, strict liability, or tort (including 
negligence or otherwise) arising in any way out of the use of this 
software, even if advised of the possibility of such damage.

Suggested reference for this work is:
@inproceedings{GZ03,
    author = "Gosta Grahne and Jianfei Zhu",
    title = "Efficiently Using Prefix-trees in Mining Frequent Itemsets",
    booktitle = "{FIMI'03} Workshop on Frequent Itemset Mining Implementations",
    month = "November",
    year = "2003",
    location = "Melbourne, FL",
}

////////////////////////////////////////////////////////////////


Contact: dongxin@uiuc.edu

Reference: Dong Xin, Jiawei Han, Xifeng Yan, Hong Cheng, 
Mining Compressed Frequent-Pattern Set, 
Proceedings of 2005 Int. Conf. on Very Large Data Bases (VLDB 2005).

How-To:
    rpmine filename min_sup delta outfile

    Note: rpmine corresponds to RPlocal in the paper.

    Parameters: (1) filename, input file (2) min_sup, the
    minimum frequency of patterns (3) delta, the error torrlence (4)
    outfile, the output file.

    Example:
        compress infile 0.5 0.1 outfile
        It mines all frequent sequences from "infile", each of which
        should appear in at least 50% of the transactions in the dataset. 0.1
        means all the original patterns are covered by compressed patterns with
        distance up to 0.1.


Input Format:
    1. The input is a set of transactions; each transaction has the following
    format
    
    item_1 item_2 ... item_n
    
    Each transaction takes a line.
    

    Example:
        1 2 3 4
        2 3 4 5
        ...


Output:
    The discovered patterns are stored in outfile,
    which is in a format of plain text.
    Each line of the output file has the following format
    item_1 item_2 ... item_m (support)
