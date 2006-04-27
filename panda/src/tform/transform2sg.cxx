// Filename: transform2sg.cxx
// Created by:  drose (12Mar02)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#include "transform2sg.h"
#include "transformState.h"
#include "dataNodeTransmit.h"
#include "dataGraphTraverser.h"


TypeHandle Transform2SG::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: Transform2SG::Constructor
//       Access: Public
//  Description:
////////////////////////////////////////////////////////////////////
Transform2SG::
Transform2SG(const string &name) :
  DataNode(name)
{
  _transform_input = define_input("transform", TransformState::get_class_type());

  _node = NULL;
}

////////////////////////////////////////////////////////////////////
//     Function: Transform2SG::set_node
//       Access: Public
//  Description: Sets the node that this object will adjust.
////////////////////////////////////////////////////////////////////
void Transform2SG::
set_node(PandaNode *node) {
  _node = node;
}

////////////////////////////////////////////////////////////////////
//     Function: Transform2SG::get_node
//       Access: Public
//  Description: Returns the node that this object will adjust, or NULL
//               if the node has not yet been set.
////////////////////////////////////////////////////////////////////
PandaNode *Transform2SG::
get_node() const {
  return _node;
}


////////////////////////////////////////////////////////////////////
//     Function: Transform2SG::do_transmit_data
//       Access: Protected, Virtual
//  Description: The virtual implementation of transmit_data().  This
//               function receives an array of input parameters and
//               should generate an array of output parameters.  The
//               input parameters may be accessed with the index
//               numbers returned by the define_input() calls that
//               were made earlier (presumably in the constructor);
//               likewise, the output parameters should be set with
//               the index numbers returned by the define_output()
//               calls.
////////////////////////////////////////////////////////////////////
void Transform2SG::
do_transmit_data(DataGraphTraverser *trav, const DataNodeTransmit &input,
                 DataNodeTransmit &) {
  Thread *current_thread = trav->get_current_thread();

  if (input.has_data(_transform_input)) {
    const TransformState *transform;
    DCAST_INTO_V(transform, input.get_data(_transform_input).get_ptr());
    if (_node != (PandaNode *)NULL) {
      _node->set_transform(transform, current_thread);
    }
  }
}
