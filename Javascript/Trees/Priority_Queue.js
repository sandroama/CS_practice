// Priority Queue is an extension of Queue having some properties as follows: 

// Each element of the priority queue has a priority associated with it.
// Elements are added to the queue as per the priority.
// Lowest priority elements are removed first.

// User defined class
// to store element and its priority
class QElement {
	constructor(element, priority)
	{
		this.element = element;
		this.priority = priority;
	}
}

// PriorityQueue class
class PriorityQueue {

	// An array is used to implement priority
	constructor()
	{
		this.items = [];
	}

    // enqueue function to add element
    // to the queue as per priority
    enqueue(element, priority){

	// creating object from queue element
	var qElement = new QElement(element, priority);
	var contain = false;

	// iterating through the entire
	// item array to add element at the
	// correct location of the Queue
	for (var i = 0; i < this.items.length; i++) {
		if (this.items[i].priority > qElement.priority) {
			// Once the correct location is found it is
			// enqueued
			this.items.splice(i, 0, qElement);
			contain = true;
			break;
		}
	}

	// if the element have the highest priority
	// it is added at the end of the queue
	if (!contain) {
		this.items.push(qElement);
	}
}

	//// functions to be implemented
	// dequeue()
	// front()
	// isEmpty()
	// printPQueue()
}
