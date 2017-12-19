use std::rc::Rc;
use std::cell::{Ref, RefCell, RefMut};

// 想要使用 trait 统一 List 和Node，
// 然后统一操作。现在看来，并不是那么容易的。

// pub struct List<T> {
//     head: Link<T>,
//     tail: Link<T>,
// }

// type Link<T> = Option<Rc<RefCell<Node<T>>>>;

// struct Node<T> {
//     elem: T,
//     next: Link<T>,
//     prev: Link<T>,
// }

// trait Linked {
//     type NodePtr;
//     type Node;

//     fn prev(&self) -> Option<Self::NodePtr>;

//     fn next(&self) -> Option<Self::NodePtr>;

//     fn set_next(&mut self, Self::NodePtr);

//     fn set_prev(&mut self, Self::NodePtr);

//     fn connect(left: &mut Self::Node, right: &mut Self::Node) {
//         left.
//     }
// }

// impl<T> Linked for List<T> {
//     type NodePtr = Rc<RefCell<Node<T>>>;

//     fn prev(&self) -> Option<Self::NodePtr> {
//         self.tail
//     }
//     fn next(&self) -> Option<Self::NodePtr> {
//         self.head
//     }
//     fn set_next(&mut self, ptr: Self::NodePtr) {
//         self.next = Some(ptr);
//     }
//     fn set_prev(&mut self, ptr: Self::NodePtr) {
//         self.prev = Some(ptr);
//     }
// }
