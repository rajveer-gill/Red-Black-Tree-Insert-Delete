#include "rbt.h"

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}



// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
    /* TODO */
	RBTNode* leftNode = static_cast<RBTNode*>(y->get_left());
	RBTNode* rightOfLeftNode = static_cast<RBTNode*>(leftNode->get_right());
	RBTNode* parentNode = static_cast<RBTNode*>(y->get_parent());

	y->add_left(rightOfLeftNode);
	if (rightOfLeftNode != get_sentinel()) {
    		rightOfLeftNode->add_parent(y);
	}

	leftNode->add_parent(parentNode);
	if (parentNode == get_sentinel()) {
    		root = leftNode;
	} 
	else if (y == parentNode->get_right()) {
    		parentNode->add_right(leftNode);
	} 
	else {
    		parentNode->add_left(leftNode);
	}

	leftNode->add_right(y);
	y->add_parent(leftNode);

}
// Left rotate
void RBT::left_rotate(RBTNode* x)
{
    /* TODO */
	RBTNode* rightChild = static_cast<RBTNode*>(x->get_right());
	RBTNode* leftOfRightChild = static_cast<RBTNode*>(rightChild->get_left());
	RBTNode* parentNode = static_cast<RBTNode*>(x->get_parent());

	x->add_right(leftOfRightChild);
	if (leftOfRightChild != get_sentinel()) {
    		leftOfRightChild->add_parent(x);
	}

	rightChild->add_parent(parentNode);
	if (parentNode == get_sentinel()) {
    		root = rightChild;
	} 
	else if (x == parentNode->get_left()) {
    		parentNode->add_left(rightChild);
	} 
	else {
    		parentNode->add_right(rightChild);
	}

	rightChild->add_left(x);
	x->add_parent(rightChild);
 
}
void RBT::rb_insert_fixup(RBTNode* in)
{
    /* TODO */
	RBTNode* pNode = static_cast<RBTNode*>(in->get_parent());
	RBTNode* gpNode = static_cast<RBTNode*>(pNode->get_parent());

	while (pNode->get_color() == RED) {
    		RBTNode* parent = static_cast<RBTNode*>(in->get_parent());
    		RBTNode* gParent = static_cast<RBTNode*>(parent->get_parent());

    		if (parent == static_cast<RBTNode*>(gParent->get_left())) {
        		RBTNode* uNode = static_cast<RBTNode*>(gParent->get_right());

        		if (uNode->get_color() == RED) {
            			parent->add_color(BLACK);
            			uNode->add_color(BLACK);
            			gParent->add_color(RED);
            			in = gParent;
        		}
		       	else {
            			if (in == parent->get_right()) {
                			in = parent;
                			left_rotate(in);
                			parent = static_cast<RBTNode*>(in->get_parent());
                			gParent = static_cast<RBTNode*>(parent->get_parent());
            			}
            			parent->add_color(BLACK);
            			gParent->add_color(RED);
            			right_rotate(gParent);
        		}
    		} 
		else {
        		RBTNode* uNode = static_cast<RBTNode*>(gParent->get_left());

        		if (uNode != get_sentinel() && uNode->get_color() == RED) {
            			parent->add_color(BLACK);
            			uNode->add_color(BLACK);
            			gParent->add_color(RED);
            			in = gParent;
        		}
		       	else {
            			if (in == parent->get_left()) {
                			in = parent;
                			right_rotate(in);
                			parent = static_cast<RBTNode*>(in->get_parent());
                			gParent = static_cast<RBTNode*>(parent->get_parent());
            			}
            			parent->add_color(BLACK);
            			gParent->add_color(RED);
            			left_rotate(gParent);
        		}
    		}

    		pNode = static_cast<RBTNode*>(in->get_parent());
    		gpNode = static_cast<RBTNode*>(pNode->get_parent());
	}

	static_cast<RBTNode*>(root)->add_color(BLACK);

}

void RBT::rb_insert_node(RBTNode* in)
{
    /* TODO */
    BST::insert_node(in, sentinel);
    in->add_right(get_sentinel());
    in->add_left(get_sentinel()); 
    in->add_color(RED);
    if(in->get_parent() == nullptr) {
        in->add_parent(get_sentinel());
    }

    rb_insert_fixup(in);
}

void RBT::rb_delete_fixup(RBTNode* in)
{
    /* TODO */
	RBTNode* node = in;

	while (node != root && node->get_color() == BLACK) {
		RBTNode* parentNode = static_cast<RBTNode*>(node->get_parent());
		RBTNode* siblingNode;

		if (node == parentNode->get_left()) {
			siblingNode = static_cast<RBTNode*>(parentNode->get_right());

			if (siblingNode->get_color() == RED) {
				siblingNode->add_color(BLACK);
				parentNode->add_color(RED);
				left_rotate(parentNode);
				parentNode = static_cast<RBTNode*>(node->get_parent());
				siblingNode = static_cast<RBTNode*>(parentNode->get_right());
			}

			if (static_cast<RBTNode*>(siblingNode->get_left())->get_color() == BLACK && static_cast<RBTNode*>(siblingNode->get_right())->get_color() == BLACK) {
				siblingNode->add_color(RED);
				node = parentNode;
			} else {
				if (static_cast<RBTNode*>(siblingNode->get_right())->get_color() == BLACK) {
					static_cast<RBTNode*>(siblingNode->get_left())->add_color(BLACK);
					siblingNode->add_color(RED);
					right_rotate(siblingNode);
					siblingNode = static_cast<RBTNode*>(parentNode->get_right());
				}

				siblingNode->add_color(parentNode->get_color());
				parentNode->add_color(BLACK);
				static_cast<RBTNode*>(siblingNode->get_right())->add_color(BLACK);
				left_rotate(parentNode);
				node = static_cast<RBTNode*>(root);
			}
		}
	       	else {
			siblingNode = static_cast<RBTNode*>(parentNode->get_left());

			if (siblingNode->get_color() == RED) {
				siblingNode->add_color(BLACK);
				parentNode->add_color(RED);
				right_rotate(parentNode);
				parentNode = static_cast<RBTNode*>(node->get_parent());
				siblingNode = static_cast<RBTNode*>(parentNode->get_left());
			}

			if (static_cast<RBTNode*>(siblingNode->get_right())->get_color() == BLACK && static_cast<RBTNode*>(siblingNode->get_left())->get_color() == BLACK) {
				siblingNode->add_color(RED);
				node = parentNode;
			} 
			else {
				if (static_cast<RBTNode*>(siblingNode->get_left())->get_color() == BLACK) {
					static_cast<RBTNode*>(siblingNode->get_right())->add_color(BLACK);
					siblingNode->add_color(RED);
					left_rotate(siblingNode);
					siblingNode = static_cast<RBTNode*>(parentNode->get_left());
				}

				siblingNode->add_color(parentNode->get_color());
				parentNode->add_color(BLACK);
				static_cast<RBTNode*>(siblingNode->get_left())->add_color(BLACK);
				right_rotate(parentNode);
				node = static_cast<RBTNode*>(root);
			}
		}
	}

	node->add_color(BLACK);

}

void RBT::rb_delete_node(RBTNode* out)
{
    /* TODO */
    RBTNode* nodeToRemove;
    RBTNode* nodeToFix;
    RBTNode* nodeParent;
    Node_color originalNodeColor;

    if (out->get_left() == sentinel || out->get_right() == sentinel) {
        nodeToRemove = out;
    } else {
        nodeToRemove = get_succ(out);
    }

    originalNodeColor = nodeToRemove->get_color();
    nodeParent = static_cast<RBTNode*>(nodeToRemove->get_parent());

    if (nodeToRemove->get_left() != sentinel) {
        nodeToFix = static_cast<RBTNode*>(nodeToRemove->get_left());
    } else {
        nodeToFix = static_cast<RBTNode*>(nodeToRemove->get_right());
    }
    nodeToFix->add_parent(nodeParent);

    if (nodeParent == sentinel) {
        root = nodeToFix;
    } else if (nodeToRemove == nodeParent->get_left()) {
        nodeParent->add_left(nodeToFix);
    } else {
        nodeParent->add_right(nodeToFix);
    }

    if(nodeToRemove != out){
        if (out->get_left() != nodeToRemove) {
            nodeToRemove->add_left(out->get_left());
            out->get_left()->add_parent(nodeToRemove);
        }
        if (out->get_right() != nodeToRemove) {
            nodeToRemove->add_right(out->get_right());
            out->get_right()->add_parent(nodeToRemove);
        }
        nodeToRemove->add_parent(out->get_parent());
        if (nodeToRemove->get_parent() == sentinel) {
            root = nodeToRemove;
        } else if (out == out->get_parent()->get_left()) {
            out->get_parent()->add_left(nodeToRemove);
        } else {
            out->get_parent()->add_right(nodeToRemove);
        }
        nodeToRemove->add_color(out->get_color());
    }

    
    delete out;
    if (originalNodeColor == BLACK) {
        rb_delete_fixup(nodeToFix);
    } 
}

// ---------------------------------------
