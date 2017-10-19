use std::ptr::{self, Shared};
use boxed::{Box, IntermediateBox};

pub mod study{

	pub struct ListNode<T>{
		next: Option<Shared<Node<T>>>,
		prev: Option<Shared<Node<T>>>,
	}

	impl<T> ListNode<T>{
		fn new(element: T) -> Self {
			ListNode {
				next: None,
				prev: None,
			}
		}

		fn connect(mut node1: Box<Node<T>>,mut node2: Box<Node<T>>){
			unimplemented!();
		}
	}

	pub struct Node<T>{
		list_node: ListNode<T>,
		element: T,
	}

	impl<T> Node<T> {
		fn new(element: T) -> Self {
			Node {
				next: None,
				prev: None,
				element: T,
			}
		}

		fn into_element(self: Box<Self>) -> T {
			self.element
		}

		fn connect()
	}

	pub struct LinkedList<T> {
		root: ListNode<T>,
		len: usize,
	}


	impl<T> LinkedList<T>{

		fn new() -> RetType {
			LinkedList<T>{
				None,
				None,
				0,				
			}
		}

		fn push_front_node(self,mut node:Box<None<T>>) {
			
		}

		fn push_back_node(self,mut node:Box<None<T>>) {

		}
	}
}