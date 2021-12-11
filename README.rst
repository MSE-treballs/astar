Implementation of the A* algorithm
==================================

The A* algorithm is a graph traversal and path search algorithm designed to
solve the routing problem. This is our preferred solution to this problem,
since it is complete, optimal and computationally efficient, meaning it will
always find an optimal solution (given that one exists), and will do so
efficiently.

By employing an heuristic function, which by definition is able to
underestimate the actual cost of travelling from one node to the goal, the A*
algorithm is able to take informed decisions which enable it to, in most cases,
outperform non-guided algorithms.

This particular implementation of the algorithm prioritises efficiency, and
does so by applying several optimisation techniques, without sacrificing
precision nor violating the problem's nature.

.. code::

    jgs       .---;-,
           __/_,{)|__;._                 
        ."` _     :  _  `.  .:::;.    .::'
        '--(_)------(_)--' `      '::' 

How to use
----------

To compile the code make sure to have an :code:`obj/` folder available in the
root directory, then run the following commands

.. code::

   $ make
   $ ./astar

To visualise the resulting path, the output can be redirected to a file, which
can be easily plotted in `GPSVisualizer <https://www.gpsvisualizer.com/>`_.

Input format
------------

The program will try to parse a graph of nodes and ways with the following
format

.. code::

   node|@id|@name|@place|@highway|@route|@ref|@oneway|@maxspeed|node_lat|node_lon
   way|@id|@name|@place|@highway|@route|@ref|@oneway|@maxspeed|membernode|membernode|membernode|...
   relation|@id|@name|@place|@highway|@route|@ref|@oneway|@maxspeed|rel_type|type;@id;@role|...

The entries should be sorted by type (:code:`node`, then :code:`way`, then
:code:`relation`), and then by :code:`id`, and the only fields that will be
used are :code:`id`, :code:`node_lat`, :code:`node_lon`, :code:`oneway` and
:code:`membernode`. Relations will be ignored.

Files with such format can be downloaded from
`here (348.5Mb) <http://lluis-alseda.cat/MasterOpt/spain.csv.zip>`_ and
`here (51.9Mb) <http://lluis-alseda.cat/MasterOpt/catalunya.csv.zip>`_.

Credits
-------

This code was developed by Gerard Alcaina Rovira, Adrià Bonet Fernández and
Claudi Lleyda Moltó as an assignment for the Optimisation class in the
Modelling for Science and Engineering master's degree.
