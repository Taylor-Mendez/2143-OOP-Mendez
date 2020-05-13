#### sprite subsection of config:
- width: controls the width of each sprite
- height: controls the height of each sprite
- speed: controls the speed of each sprite

#### game subsection of config:
- width: width of the window
- height: height of the window
- day: the starting day of the simulation
- loop_count: used to keep track of game loop count
- day_ratio: used to control the ration of loop_count to days 
- communities: number of communities       (*note: can be an even number from 0-8)

#### in sim subsection of config:
- social_distancing: bool value to determine whether or not the sprites will be social distancing
- social_distance: used to increase or decrease the bounding box of each sprite to emulate social distancing
- infection_radius:
- population_count:
- initial_infected:
- initial_susceptible_ratio:
- initial_recovered_ratio:
- recovery_rate:
- percent_selfish:
- travel_rate:
