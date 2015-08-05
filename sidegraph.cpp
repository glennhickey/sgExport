/*
 * Copyright (C) 2015 by Glenn Hickey (hickey@soe.ucsc.edu)
 *
 * Released under the MIT license, see LICENSE.txt
 */

#include "sidegraph.h"

using namespace std;

const SGPosition SideGraph::NullPos(-1, -1);

SideGraph::SideGraph()
{

}

SideGraph::~SideGraph()
{
  for (JoinSet::iterator i = _joinSet.begin(); i != _joinSet.end(); ++i)
  {
    delete *i;
  }

  for (SequenceSet::iterator i = _seqSet.begin(); i != _seqSet.end(); ++i)
  {
    delete *i;
  }
}

bool SideGraph::operator==(const SideGraph& sg) const
{
  if (getNumSequences() != sg.getNumSequences() ||
      _joinSet.size() != sg._joinSet.size())
  {
    return false;
  }

  for (int i = 0; i < getNumSequences(); ++i)
  {
    if (*getSequence(i) != *sg.getSequence(i))
    {
      return false;
    }
  }
  
  JoinSet::const_iterator i = _joinSet.begin();
  JoinSet::const_iterator j = sg._joinSet.begin();
  for (; i != _joinSet.end(); ++i, ++j)
  {
    if (**i != **j)
    {
      return false;
    }
  }
  return true;
}

ostream& operator<<(ostream& os, const SideGraph& sg)
{
  os << "SideGraph {\n";
  sg_int_t i = 0;
  for (; i < sg.getNumSequences(); ++i)
  {
    os << "Sequence " << i << ": " << *sg.getSequence(i) << "\n";
  }
  const SideGraph::JoinSet* js = sg.getJoinSet();
  i = 0;
  for (SideGraph::JoinSet::const_iterator j = js->begin(); j != js->end(); ++j)
  {
    os << "Join " << i++ << ": " << **j << "\n";
  }
  return os << "}" << endl;
}
