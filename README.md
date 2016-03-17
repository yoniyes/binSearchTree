# binSearchTree

An ongoing eclipse project written in C++.
The final goal is to build a working binary search tree for implementing a dictionary.

For any non-standard variable types:<br/>
<b>USE OF THE "TREE" CLASS IS ONLY PERMITTED WITH COMPARISON OPERATORS OVERLOADING.</b>

- Provided with a basic linkedList class.

<h3>The interface for binSearchTree:</h3>
<ul>
<li><b>get()</b> - Recieves a key and returns the value.</li>
<li><b>insert()</b> - Recieves a pair (key, value) and inserts them to the tree. Returns true if the key already existed (and writes the new value instead of the old) or false if the key is a new entry.</li>
<li><b>remove()</b> - Recieves a key, removes the pair from the tree and re-builds the tree.</li>
<li><b>get_size()</b> - Returns the number of nodes in the tree.</li>
<li><b>get_root()</b> - Returns a pointer to the root node of the tree. Shouldn't be used except for debugging, mostly.</li>
<li><b>printTree()</b> - Prints the structure of the tree. For easier debugging.</li>
<li><b>export_inorder()</b> - In development. For future tree manipulation in O(n) run-time complexity.</li>
</ul>

