CAT++, CAT Array Templates, is a library for arrays in C++.

The main purpose of CAT++ is to provide support for arrays with a similar interface to that of Fortran90, respecting the copy semantics of C++, but avoiding unnecessary copy of data.

CAT++ started in 2004 as part of some R&D codes which I have written. In 13/1/2005, I have submitted the code for publication at GNA (https://gna.org/projects/cat), under GPLV2 license. At 26/11/2007, the project moved to Google Code.

The storage backend code has been written from scratch using new/delete and reference counting techniques. Alternative storage backends will probably be implemented in the future, probably based on STL containers.

This project uses some techniques similar to those used in Blitz++ (http://www.oonumerics.org/blitz/), which is a similar library using reference semantics. It was a source of inspiration and knowledge. Therefore, I would like to thank the Blitz++ development team.

Credits are due to Jose Matos (jamatos@fc.up.pt) for the recursive acronym. Also a special thank you for all his support, encouragement and mentoring as I started learning and developing in C++.

Feedback and help is of course more than welcome. I hope this piece of software may be of use. Enjoy,

Manuel Baptista