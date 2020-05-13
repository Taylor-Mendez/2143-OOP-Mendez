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

#### sim subsection of config:
- social_distancing: bool value to determine whether or not the sprites will be social distancing
- social_distance: used to increase or decrease the bounding box of each sprite to emulate social distancing
- infection_radius: 
- population_count: number of sprites in population
- initial_infected_ratio: can be a number between 0-1, used to determine percentage of the population_count that
starts out infected (*note: initial_infected_ratio, initial_susceptible_ratio, and initial_recovered_ratio should all add up to 1)
- initial_susceptible_ratio: can be a number between 0-1, used to determine percentage of the population_count that
starts out susceptible
- initial_recovered_ratio: can be a number between 0-1, used to determine percentage of the population_count that
starts out recovered
- recovery_rate: the number of days it takes for a person to recover from infection
- percent_selfish: the percentage of the population that do not follow social distancing rules
- travel_rate: 
