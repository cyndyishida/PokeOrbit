# PokeOrbit
MFC Application Game written in Visual C++ with Multithreading through OpenMP, equipted with a testing project


![alt](http://cyndyishida.me/assets/img/projects/pokeorbit.jpg)


## Features & Functionality
* The circle in the middle is the playing area. Pokemon and Pokestops appear at random intervals in the playing area. They rotate around the center at random speeds. 

* Some Pokemon are naturally faster than others. When you click inside the circle, you launch a Pokeball. 

* It launches in the direction you have clicked relative to the center. How fast it moves depends on how far out from the center you click. If you click 1/2 way to the edge, it moves half that speed. 

* Clicks outside the circle have no effect. If the Pokeball hits a Pokemon the Pokemon disappears and is added to the count of caught Pokemon on the right. 

* The maximum number of Pokeballs you can have is 13. If you are out, you can't launch. On an occasional basis, Pokestops appear and also rotate around the center of the playing space, though somewhat slower. 

* If you click on a Pokestop, you get 3 new Pokeballs. One you click on a Pokestop, it turns purple and you cannot click on it again for 15 seconds, after which it turns blue again and you can again use it. 

* After 60 seconds a Pokestop disappears. Pokestops appear less frequently and move slower.



## Goals
- [ ] Test on machine that with more processors, being able to better see the speed up with increasing threads
