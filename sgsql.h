/*
 * Copyright (C) 2015 by Glenn Hickey (hickey@soe.ucsc.edu)
 *
 * Released under the MIT license, see LICENSE.cactus
 */

#ifndef _SGSQL_H
#define _SGSQL_H

#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

#include "sidegraph.h"

/*
 * write a SideGraph to GA4GH SQL format.  This will be a fasta file with
 * the sequence information and a .sql file with a bunch of INSERT statements
 * that can be loaded into a db.  
 *
 * code originally written for hal2sg, which maps somewhat awkwardly to 
 * variants, alleles, etc coming from multi-genome alignment.  this class can
 * get built up to be more general as needed....
 */

class SGSQL
{
public:
   SGSQL();
   virtual ~SGSQL();

protected:

   /** call the functions below to write everything 
    */
   virtual void writeDb(const SideGraph* sg,
                        const std::string& sqlInsertPath,
                        const std::string& fastaPath);

   /** get DNA string corresponding to a sequence 
    */
   virtual void getSequenceString(const SGSequence* seq,
                                  std::string& outString) const = 0;

   /** determine name of input sequence from which this sequence was
    * derived.  
    */
   virtual std::string getOriginName(const SGSequence* seq) const = 0;

   /** Which origin name do we consider primary? Used to name ReferenceSet
    */
   virtual std::string getPrimaryOriginName() const = 0;

   /** Get description for reference set 
    */
   virtual std::string getDescription() const = 0;

   /** write out the FASTA file by using the back map in sgBuilder
    * to convert sideGraph sequences back into their hal coordinates, then
    * pulling the DNA string out of HAL.  also fill in the checksum map
    * as we go.
    */
   virtual void writeFasta();

   /** write an INSERT for the fasta file.  We only make one so its 
    * ID is always 0
    */
   virtual void writeFastaInsert();
   
   /** write an INSERT for each join the graph
    */
   virtual void writeJoinInserts();

   /** write an INSERT for each sequence in the graph
    */
   virtual void writeSequenceInserts();

   /** write a "Reference" INSERT for each sequence in the graph into
    * one Reference set. 
    */
   virtual void writeReferenceInserts();

   /** write path INSERTs (makes a VariantSet for each Genome and 
    * an Allele for each sequence
    */
   // NOTE TO SELF: should move some code up from halsgsql for this
   virtual void writePathInserts() = 0;

   static void getChecksum(const std::string& inputString,
                           std::string& outputString);

protected:

   const SideGraph* _sg;
   std::string _outPath;
   std::string _faPath;
   std::string _halPath;
   std::ofstream _outStream;
   std::ofstream _faStream;
   std::map<sg_int_t, std::string> _checksumMap;
};


#endif
