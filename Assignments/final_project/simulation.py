# Import and initialize the pygame library
import pygame
import random
import math
import sys,os
import json

# list of colors
colors = ["blue", "light_blue", "yellow", "red", "green"]

# list of states
state = ["susceptible", "infected", "recovered"]

# read in data from config.json
if os.path.isfile("config.json"):
    f = open("config.json","r")
    data = f.read()
    config = json.loads(data)
    for key in config:
        print(config[key])


# /$$$$$$$  /$$$$$$$$ /$$$$$$$   /$$$$$$   /$$$$$$  /$$   /$$
#| $$__  $$| $$_____/| $$__  $$ /$$__  $$ /$$__  $$| $$$ | $$
#| $$  \ $$| $$      | $$  \ $$| $$  \__/| $$  \ $$| $$$$| $$
#| $$$$$$$/| $$$$$   | $$$$$$$/|  $$$$$$ | $$  | $$| $$ $$ $$
#| $$____/ | $$__/   | $$__  $$ \____  $$| $$  | $$| $$  $$$$
#| $$      | $$      | $$  \ $$ /$$  \ $$| $$  | $$| $$\  $$$
#| $$      | $$$$$$$$| $$  | $$|  $$$$$$/|  $$$$$$/| $$ \  $$
#|__/      |________/|__/  |__/ \______/  \______/ |__/  \__/

class Person(pygame.sprite.Sprite):
    """
    This class represents the ball.
    It derives from the "Sprite" class in Pygame
    """
    def __init__(self, **kwargs):
        """ Constructor. 
        """

        # Call the parent class (Sprite) constructor
        super().__init__()
        self.width = kwargs.get("width", 10)
        self.height = kwargs.get("height", 10)
        self.speed = kwargs.get("speed", 1)
        self.coord = kwargs.get("coord", None)
        self.state = kwargs.get("state", "susceptible")
        self.color = kwargs.get("color", "green")
        self.community = kwargs.get("community")


        # might not work
        self.x1 = self.community.getx1()
        self.y1 = self.community.gety1()
        self.x2 = self.community.getx2()
        self.y2 = self.community.gety2()
        self.community_id = self.community.getCommunityId()

        # choose sprite direction
        self.dx = 0
        self.dy = 0
        while self.dx + self.dy == 0:
            self.dx = random.choice([1, -1, 0])
            self.dy = random.choice([1, -1, 0])

        # give our sprite an image and resize it
        self.image = pygame.image.load(config["images"][self.color])
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

        # set sprite position
        self.x = random.randint(int(self.x1), int(self.x2))
        self.y = random.randint(int(self.y1), int(self.y2))

        # sprite bounding rectangle
        self.rect = self.image.get_rect(center=(self.x, self.y))

    def __repr__(self):
        ''' Representation or a unambigous printout of your object
        '''
        return self.__str__()

    def __str__(self):
        ''' String printout of your object
        '''
        c = self.color
        s = self.speed
        x = self.x
        y = self.y
        r = self.rect 
        return f"Color: {c}, Speed: {s}, X: {x}, Y: {y}, Rect: {r} "

    def printcoords(self):
        print(self.x)
        print(self.y)

    def setSocialDistance(self,distance):
        self.rect = self.rect.inflate(distance,distance)

#___________________________________________________________________________
# Description: gets the day that the sprite was infected
#
# Params: enon
#
# returns: none
#____________________________________________________________________________ 
    def getLastInfected(self):
        return (self.last_infected)

#___________________________________________________________________________
# Description: sets the day that the sprite was infected
#
# Params: the day of the simulation
#
# returns: none
#____________________________________________________________________________ 
    def setLastInfected(self,num):
        self.last_infected = num  

#___________________________________________________________________________
# Description: sets the day infected of sprite who were initially infected to
#              day 0
#
# Params: none
#
# returns: none
#____________________________________________________________________________ 
    def setInitialLastInfected(self):
        self.last_infected = 0

    def setColor(self,color): 
        self.color = color
        self.image = pygame.image.load(config["images"][self.color])
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

    def getColor(self):
        return (self.color)

    def getState(self):
        return(self.state)

    def setState(self,state):
        self.state = state

    def setDxDy(self, dx, dy):
        self.dx = dx
        self.dy = dy

    def getDxDy(self):
        return (self.dx, self.dy)

    def changeDirection(self, sides_contacted):
        if sides_contacted["top"]:
            self.dy = 1
        if sides_contacted["bottom"]:
            self.dy = -1
        if sides_contacted["left"]:
            self.dx = 1
        if sides_contacted["right"]:
            self.dx = -1

    def move(self):

        sides_contacted = self.checkWalls()

        self.changeDirection(sides_contacted)

        if self.dx < 0:
            self.rect.x -= self.speed
        elif self.dx > 0:
            self.rect.x += self.speed

        if self.dy < 0:
            self.rect.y -= self.speed
        elif self.dy > 0:
            self.rect.y += self.speed

    def checkCollide(self, other):
        sides_contacted = {
            "top": False,
            "bottom": False,
            "left": False,
            "right": False
        }

        if self.rect.colliderect(other.rect):

            if self.rect.top < other.rect.top:
                sides_contacted["bottom"] = True
                self.rect.y -= abs(self.rect.y - other.rect.y) // 8
            if self.rect.left < other.rect.left:
                sides_contacted["right"] = True
                self.rect.x -= abs(self.rect.x - other.rect.x) // 8
            if self.rect.right > other.rect.right:
                sides_contacted["left"] = True
                self.rect.x += abs(self.rect.x - other.rect.x) // 8
            if self.rect.bottom > other.rect.bottom:
                sides_contacted["top"] = True
                self.rect.y += abs(self.rect.y - other.rect.y) // 8

                self.changeDirection(sides_contacted)

                return True

        return False

#___________________________________________________________________________
# Description: gets the distance between two sprites
#
# Params: instance of another sprite, the social distance, and the infection 
#         radius
#
# returns: bool (true indicates that the distance between the two sprites
#          was less than the social distance))
#____________________________________________________________________________
    def checkSocialDistace(self,other, social_distance,infection_radius):
        # get distance
        x1,y1 = self.rect.center
        x2,y2 = other.rect.center

        d = abs(math.sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)))

        if d <= infection_radius:
            return True


    def checkWalls(self):
        sides = {"top": False, "bottom": False, "left": False, "right": False}

        if self.rect.top <= self.y1:
            sides["top"] = True
        if self.rect.left <= self.x1:
            sides["left"] = True
        if self.rect.right >= self.x2:
            sides["right"] = True
        if self.rect.bottom >= self.y2:
            sides["bottom"] = True

        return sides

#___________________________________________________________________________
# Description: gives the sprite a new community and changes the bounds in
#              which it can travel and community_id accordingly
#
# Params: a new Community
#
# returns: none
#____________________________________________________________________________    
    def changeCommunity(self,community):
        self.community = community

        self.x1 = self.community.getx1()
        self.y1 = self.community.gety1()
        self.x2 = self.community.getx2()
        self.y2 = self.community.gety2()

        self.x = random.randint(int(self.community.getx1()), int(self.community.getx2()))
        self.y = random.randint(int(self.community.gety1()), int(self.community.gety2()))
        self.community_id = self.community.getCommunityId()

#___________________________________________________________________________
# Description: gets the community_id of the sprite
#
# Params: none
#
# returns: community_id of the sprite
#____________________________________________________________________________ 
    def getCommunityId(self):
        return self.community_id




# /$$$$$$$   /$$$$$$  /$$$$$$$  /$$   /$$ /$$        /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$  /$$   /$$
#| $$__  $$ /$$__  $$| $$__  $$| $$  | $$| $$       /$$__  $$|__  $$__/|_  $$_/ /$$__  $$| $$$ | $$
#| $$  \ $$| $$  \ $$| $$  \ $$| $$  | $$| $$      | $$  \ $$   | $$     | $$  | $$  \ $$| $$$$| $$
#| $$$$$$$/| $$  | $$| $$$$$$$/| $$  | $$| $$      | $$$$$$$$   | $$     | $$  | $$  | $$| $$ $$ $$
#| $$____/ | $$  | $$| $$____/ | $$  | $$| $$      | $$__  $$   | $$     | $$  | $$  | $$| $$  $$$$
#| $$      | $$  | $$| $$      | $$  | $$| $$      | $$  | $$   | $$     | $$  | $$  | $$| $$\  $$$
#| $$      |  $$$$$$/| $$      |  $$$$$$/| $$$$$$$$| $$  | $$   | $$    /$$$$$$|  $$$$$$/| $$ \  $$
#|__/       \______/ |__/       \______/ |________/|__/  |__/   |__/   |______/ \______/ |__/  \__/

class Population:
    def __init__(self, **kwargs):
        self.population = []
        self.game_width = kwargs.get("width", 500)
        self.game_height = kwargs.get("height", 500)
        self.population_count = kwargs.get("population_count", 10)
        self.sprite_group = pygame.sprite.Group()
        self.screen = kwargs.get("screen", None)
        self.susceptible = int(self.population_count * config["sim"]["initial_susceptible_ratio"])
        self.infected = int(self.population_count * config["sim"]["initial_infected_ratio"])
        self.recovered = int(self.population_count * config["sim"]["initial_recovered_ratio"])
        self.numberOfCommunities = kwargs.get("communities", 4)
        self.infection_rate = kwargs.get("infection_rate", .20)
        self.recover_rate = kwargs.get("recovery_rate", 14)
        self.social_distancing = kwargs.get("social_distancing", True)
        self.social_distance = kwargs.get("social_distance", 6) 
        self.percent_selfish = kwargs.get("percent_selfish", .50) 
        self.infection_radius = kwargs.get("infection_radius", 14)
        self.travel_rate = kwargs.get("travel_rate", .35)

        #print(self.screen)
        print(self.susceptible)

        if self.screen == None:
            print(
                "Error: Simulation needs an instance of a pygame surface / screen!"
            )
            sys.exit()

    def getPopulationCount(self):
        return(self.population_count)

    def getSusceptible(self):
        return(self.susceptible)

    def getInfected(self):
        return(self.infected)

    def getRecovered(self):
        return(self.recovered)

#___________________________________________________________________________
# Description: Sets up people into communities. Changes the state and color 
#              of each sprite based on the initial number of susceptible, 
#              infected, and recovered. Sets up the number of people who 
#              adhere to social distancing based on percent_selfish
#
# Params: 
#
# returns: none
#____________________________________________________________________________ 
    def populate(self, pos=None, **kwargs):

        # need to figure out a better way to assign bounds communities to people
        for i in range(self.population_count):
            if self.numberOfCommunities > 0:
                community = Community()
                community_id = i % self.numberOfCommunities
                community.changeBounds(self.numberOfCommunities,community_id,self.game_width,self.game_height)
                self.addPerson(community=community)
            
            elif self.numberOfCommunities == 0:
                community = Community()
                community_id = 0
                community.changeBounds(self.numberOfCommunities,community_id,self.game_width,self.game_height)
                self.addPerson(community=community)

        # sets up initial infected, susceptible, infected
        for j in range(self.population_count):
            if j < int(self.population_count * config["sim"]["initial_recovered_ratio"]):
                self.population[j].setColor(colors[2])
                self.population[j].setState(state[2])
            elif j>= int(self.population_count * config["sim"]["initial_recovered_ratio"]) and j < int((self.population_count * config["sim"]["initial_recovered_ratio"]) + (self.population_count * config["sim"]["initial_infected_ratio"])):
                self.population[j].setColor(colors[3])
                self.population[j].setState(state[1])
                self.population[j].setInitialLastInfected()
            else:
                self.population[j].setState(state[0])
                self.population[j].setColor(colors[4])

        # set up social distancing
        if self.social_distancing == True:
            for k in range(self.population_count):
                # set up "selfish"
                if random.random() > self.percent_selfish:
                    self.population[k].setSocialDistance(self.social_distance)

#___________________________________________________________________________
# Description: adds a person to the population
#
# Params: can take color, state, width, height, speed, community, coords
#
# returns: none
#____________________________________________________________________________ 
    def addPerson(self, **kwargs):
        color = kwargs.get("color", random.choice(colors))
        state = kwargs.get("state","susceptible")
        width = kwargs.get("width", config["sprite"]["width"])
        height = kwargs.get("height", config["sprite"]["height"])
        speed = kwargs.get("speed", config["sprite"]["speed"])
        community = kwargs.get("community")

        x = random.randint(0, self.game_width)
        y = random.randint(0, self.game_height)
        coord = kwargs.get("coord", [x, y])

        p = Person(color=color,
                   state=state,
                   width=width,
                   height=height,
                   speed=speed,
                   coord=coord,
                   community=community)

        self.population.append(p)
        self.sprite_group.add(p)

#___________________________________________________________________________
# Description: Moves the population and checks if they have collided,
#              takes into account the rate of infection, and the infection
#              radius(if social distancing is true) when deciding whether or 
#              not a person has been infected. If a person has been infected 
#              then state and color are changed
#
# Params: day of the simulation
#
# returns: none
#____________________________________________________________________________ 
    def populationMove(self,day):
        # loop through each person and call a move method
        for i in range(len(self.population)):
            #print(self.population[i])
            self.population[i].move()
            for j in range(len(self.population)):
                if self.population[i] != self.population[j]:
                    collided = self.population[i].checkCollide(
                        self.population[j])
                    if collided:
                        dx, dy = self.population[i].getDxDy()
                        self.population[j].setDxDy(dx * -1, dy * -1)

                        # infection rate applied here
                        # also update number of people in each SIR category
                        # if social distancing on
                        if self.social_distancing == True:
                            if self.population[i].getColor() == colors[4] and self.population[j].getColor() == colors[3] and random.random() < self.infection_rate and self.population[i].checkSocialDistace(self.population[j],self.social_distance,self.infection_radius): 
                                self.population[i].setColor(colors[3])   
                                self.population[i].setState(state[1]) 
                                self.infected += 1
                                self.susceptible -=1
                                self.population[i].setLastInfected(day)                                                 
                            elif self.population[i].getColor() == colors[4] and self.population[j].getColor() == colors[3] and random.random() < self.infection_rate and self.population[i].checkSocialDistace(self.population[j],self.social_distance,self.infection_radius): 
                                self.population[i].setColor(colors[3])
                                self.population[i].setState(state[1]) 
                                self.infected += 1
                                self.susceptible -=1
                                self.population[i].setLastInfected(day)

                        if self.social_distancing == False:
                            if self.population[i].getColor() == colors[4] and self.population[j].getColor() == colors[3] and random.random() < self.infection_rate: 
                                self.population[i].setColor(colors[3])   
                                self.population[i].setState(state[1]) 
                                self.infected += 1
                                self.susceptible -=1
                                self.population[i].setLastInfected(day)                                                 
                            elif self.population[i].getColor() == colors[4] and self.population[j].getColor() == colors[3] and random.random() < self.infection_rate: 
                                self.population[i].setColor(colors[3])
                                self.population[i].setState(state[1]) 
                                self.infected += 1
                                self.susceptible -=1
                                self.population[i].setLastInfected(day)
        
        self.sprite_group.draw(self.screen)

#___________________________________________________________________________
# Description: checks if anyone in the population has recovered based on the 
#              day they were infected and the current day of the simulation
#
# Params: the day of the simulation
#
# returns: none
#____________________________________________________________________________ 
    def checkRecovery(self,day):
        for i in range(self.population_count):
            if "infected" in self.population[i].getState():
                if day - self.population[i].getLastInfected() > self.recover_rate:
                    self.population[i].setColor(colors[2])
                    self.population[i].setState(state[2])
                    self.infected -= 1
                    self.recovered +=1

#___________________________________________________________________________
# Description: Loops through the community checking to see if anyone has
#              "decided" to travel. Basically loops through the population
#              and moves them to a different community based on the 
#              travel_rate 
#
# Params: none
#
# returns: none
#____________________________________________________________________________ 
    def communityMove(self):
        for k in range(self.population_count):
            if random.random() < self.travel_rate:
                                                                                    # get new community number that is not equal to the community in now
                new_community_id =  random.randint(0,self.numberOfCommunities-1)
                while new_community_id == self.population[k].getCommunityId():          # make sure its not the same community
                    new_community_id = random.randint(0,self.numberOfCommunities-1)
                new = Community()
                new.changeBounds(self.numberOfCommunities,new_community_id,self.game_width,self.game_height)
                self.population[k].changeCommunity(new)

#  /$$$$$$   /$$$$$$  /$$      /$$ /$$      /$$ /$$   /$$ /$$   /$$ /$$$$$$ /$$$$$$$$ /$$     /$$
# /$$__  $$ /$$__  $$| $$$    /$$$| $$$    /$$$| $$  | $$| $$$ | $$|_  $$_/|__  $$__/|  $$   /$$/
#| $$  \__/| $$  \ $$| $$$$  /$$$$| $$$$  /$$$$| $$  | $$| $$$$| $$  | $$     | $$    \  $$ /$$/ 
#| $$      | $$  | $$| $$ $$/$$ $$| $$ $$/$$ $$| $$  | $$| $$ $$ $$  | $$     | $$     \  $$$$/  
#| $$      | $$  | $$| $$  $$$| $$| $$  $$$| $$| $$  | $$| $$  $$$$  | $$     | $$      \  $$/   
#| $$    $$| $$  | $$| $$\  $ | $$| $$\  $ | $$| $$  | $$| $$\  $$$  | $$     | $$       | $$    
#|  $$$$$$/|  $$$$$$/| $$ \/  | $$| $$ \/  | $$|  $$$$$$/| $$ \  $$ /$$$$$$   | $$       | $$    
# \______/  \______/ |__/     |__/|__/     |__/ \______/ |__/  \__/|______/   |__/       |__/         

class Community(object):
    def __init__(self):
        self.x1 = 0
        self.x2 = 0
        self.y1 = 0
        self.y2 = 0
        self.community_id = 0

    def setx1(self,x1):
        self.x1 = x1     
    def setx2(self,x2):
        self.x2 = x2
    def sety1(self,y1):
        self.y1 = y1
    def sety2(self,y2):
        self.y2 = y2
    def getx1(self):
        return self.x1
    def getx2(self):
        return self.x2
    def gety1(self):
        return self.y1
    def gety2(self):
        return self.y2
    def getCommunityId(self):
        return self.community_id

#________________________________________________________________________________
# Description: sets up community bounds (i.e. x1,x2,y1,y2) based on the
#              number of communities passed in. The way that community bounds are
#              set up could be done better but couldn't think of another way at the 
#              moment
#
# Params: total number of communities, community id, width (which is the 
#         game width), height (which is the game height)
#
# returns: none
#_________________________________________________________________________________ 
    def changeBounds(self,total,community_id,width,height):
        self.community_id = community_id

        if total == 0:
            self.x1 = 0
            self.x2 = width
            self.y1 = 0
            self.y2 = height
        if total == 2:
            if community_id == 0:
                self.x1 = 0
                self.x2 = width/2
                self.y1 = 0
                self.y2 = height
            elif community_id == 1:
                self.x1 = width/2
                self.x2 = width
                self.y1 = 0
                self.y2 = height
        if total == 4:
            if community_id == 0:
                self.x1 = 0
                self.x2 = width/2
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 1:
                self.x1 = width/2
                self.x2 = width
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 2:
                self.x1 = 0
                self.x2 = width/2
                self.y1 = height/2
                self.y2 = height
            elif community_id == 3:
                self.x1 = width/2
                self.x2 = width
                self.y1 = height/2
                self.y2 = height
        if total == 6:
            if community_id == 0:
                self.x1 = 0
                self.x2 = width/3
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 1:
                self.x1 = width/3
                self.x2 = (width/3)*2
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 2:
                self.x1 = (width/3)*2
                self.x2 = width
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 3:
                self.x1 = 0
                self.x2 = width/3
                self.y1 = height/2
                self.y2 = height
            elif community_id == 4:
                self.x1 = width/3
                self.x2 = (width/3)*2
                self.y1 = height/2
                self.y2 = height
            elif community_id == 5:
                self.x1 = (width/3)*2
                self.x2 = width
                self.y1 = height/2
                self.y2 = height
        if total == 8:
            if community_id == 0:
                self.x1 = 0
                self.x2 = width/4
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 1:
                self.x1 = width/4
                self.x2 = (width/4)*2
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 2:
                self.x1 = (width/4)*2
                self.x2 = (width/4)*3
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 3:
                self.x1 = (width/4)*3
                self.x2 = width
                self.y1 = 0
                self.y2 = height/2
            elif community_id == 4:
                self.x1 = 0
                self.x2 = width/4
                self.y1 = height/2
                self.y2 = height
            elif community_id == 5:
                self.x1 = width/4
                self.x2 = (width/4)*2
                self.y1 = height/2
                self.y2 = height
            elif community_id == 6:
                self.x1 = (width/4)*2
                self.x2 = (width/4)*3
                self.y1 = height/2
                self.y2 = height
            elif community_id == 7:
                self.x1 = (width/4)*3
                self.x2 = width
                self.y1 = height/2
                self.y2 = height 

# /$$$$$$$$ /$$$$$$  /$$   /$$ /$$$$$$$$ /$$   /$$ /$$$$$$$$ /$$       /$$$$$$$  /$$$$$$$$ /$$$$$$$ 
#| $$_____//$$__  $$| $$$ | $$|__  $$__/| $$  | $$| $$_____/| $$      | $$__  $$| $$_____/| $$__  $$
#| $$     | $$  \ $$| $$$$| $$   | $$   | $$  | $$| $$      | $$      | $$  \ $$| $$      | $$  \ $$
#| $$$$$  | $$  | $$| $$ $$ $$   | $$   | $$$$$$$$| $$$$$   | $$      | $$$$$$$/| $$$$$   | $$$$$$$/
#| $$__/  | $$  | $$| $$  $$$$   | $$   | $$__  $$| $$__/   | $$      | $$____/ | $$__/   | $$__  $$
#| $$     | $$  | $$| $$\  $$$   | $$   | $$  | $$| $$      | $$      | $$      | $$      | $$  \ $$
#| $$     |  $$$$$$/| $$ \  $$   | $$   | $$  | $$| $$$$$$$$| $$$$$$$$| $$      | $$$$$$$$| $$  | $$
#|__/      \______/ |__/  \__/   |__/   |__/  |__/|________/|________/|__/      |________/|__/  |__/

# need to put all these methods into a class
                                                                                                   
def messageDisplay(text,screen):
    mediumText = pygame.font.Font('./fonts/LeagueSpartan-Bold.otf', 22)
    TextSurf,TextRect = text_objects(text,mediumText)
    TextRect.left = 0
    TextRect.top = 0
    screen.blit(TextSurf,TextRect)
    pygame.display.update()

def text_objects(text,font):
    textSurface = font.render(text,True, (255,255,255))
    return textSurface, textSurface.get_rect()

def drawCommunities(communities,width,height,screen):

    red = (255,0,0)
    if communities == 2:
        pygame.draw.line(screen,red,(width/2,0),(width/2,height),5)
    if communities == 4:
        pygame.draw.line(screen,red,(width/2,0),(width/2,height),5)
        pygame.draw.line(screen,red,(0,height/2),(width,height/2),5)

    if communities == 6:
        pygame.draw.line(screen,red,(width/3,0),(width/3,height),5)
        pygame.draw.line(screen,red,((width/3)*2,0),((width/3)*2,height),5)
        pygame.draw.line(screen,red,(0,height/2),(width,height/2),5)

    if communities == 8:
        pygame.draw.line(screen,red,(width/4,0),(width/4,height),5)
        pygame.draw.line(screen,red,((width/4)*2,0),((width/4)*2,height),5)
        pygame.draw.line(screen,red,((width/4)*3,0),((width/4)*3,height),5)
        pygame.draw.line(screen,red,(0,height/2),(width,height/2),5)

#  /$$$$$$  /$$$$$$ /$$      /$$ /$$   /$$ /$$        /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$  /$$   /$$
# /$$__  $$|_  $$_/| $$$    /$$$| $$  | $$| $$       /$$__  $$|__  $$__/|_  $$_/ /$$__  $$| $$$ | $$
#| $$  \__/  | $$  | $$$$  /$$$$| $$  | $$| $$      | $$  \ $$   | $$     | $$  | $$  \ $$| $$$$| $$
#|  $$$$$$   | $$  | $$ $$/$$ $$| $$  | $$| $$      | $$$$$$$$   | $$     | $$  | $$  | $$| $$ $$ $$
# \____  $$  | $$  | $$  $$$| $$| $$  | $$| $$      | $$__  $$   | $$     | $$  | $$  | $$| $$  $$$$
# /$$  \ $$  | $$  | $$\  $ | $$| $$  | $$| $$      | $$  | $$   | $$     | $$  | $$  | $$| $$\  $$$
#|  $$$$$$/ /$$$$$$| $$ \/  | $$|  $$$$$$/| $$$$$$$$| $$  | $$   | $$    /$$$$$$|  $$$$$$/| $$ \  $$
# \______/ |______/|__/     |__/ \______/ |________/|__/  |__/   |__/   |______/ \______/ |__/  \__/

# /$$      /$$  /$$$$$$  /$$$$$$ /$$   /$$
#| $$$    /$$$ /$$__  $$|_  $$_/| $$$ | $$
#| $$$$  /$$$$| $$  \ $$  | $$  | $$$$| $$
#| $$ $$/$$ $$| $$$$$$$$  | $$  | $$ $$ $$
#| $$  $$$| $$| $$__  $$  | $$  | $$  $$$$
#| $$\  $ | $$| $$  | $$  | $$  | $$\  $$$
#| $$ \/  | $$| $$  | $$ /$$$$$$| $$ \  $$
#|__/     |__/|__/  |__/|______/|__/  \__/

if __name__ == '__main__':
    
    pygame.init()
    pygame.display.set_caption('Corona Virus') 



    # Set up the drawing window
    screen = pygame.display.set_mode(
        [config["game"]["width"], config["game"]["height"]])

    # Set up the population
    pop = Population(screen=screen,
                     width=config["game"]["width"],
                     height=config["game"]["height"],
                     population_count=config["sim"]["population_count"],
                     communities=config["game"]["communities"],
                     day = config["game"]["day"],
                     recovery_rate = config["sim"]["recovery_rate"],
                     social_distancing=config["sim"]["social_distancing"],
                     social_distance=config["sim"]["social_distance"],
                     percent_selfish=config["sim"]["percent_selfish"],
                     infection_radius=config["sim"]["infection_radius"],
                     travel_rate=config["sim"]["travel_rate"])

    # Add people to the population
    pop.populate()

    # helps keep game loop running at
    # specific frames per second
    clock = pygame.time.Clock()

    # Run until the user asks to quit
    running = True

    #___ GAME LOOP ____________________________________________________________
    while running:
        # Fill the background with blackish
        # Do not do this after you draw sprites!
        screen.fill((30, 30, 30))
        

        # Did the user click the window close button?
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        #___CONTROL SIMULATION HERE_____________________________________________________________

        # draws community bounds
        drawCommunities(config["game"]["communities"],config["game"]["width"],config["game"]["height"],screen)

        # moves the community
        pop.populationMove(config["game"]["day"])

        # displays the the number of people susceptible, infected, and recovered to the screen
        message = "susceptible:" + str(pop.getSusceptible()) + "  infected:" + str(pop.getInfected()) + "  recovered:" + str(pop.getRecovered())
        messageDisplay(message,screen)

        #___END CONTROL SIMULATION_____________________________________________________________

        # This keeps game loop running at a constant FPS
        clock.tick(config["game"]["fps"])  # FPS = frames per second

        # Count number of loops game runs (careful, this number could get LARGE)
        config["game"]["loop_count"] += 1

        # check to see if people have recovered after every game loop
        pop.checkRecovery(config["game"]["day"])

        # controls  and updates days
        if config["game"]["loop_count"] == config["game"]["day_ratio"]:
            config["game"]["day"] +=1
            config["game"]["loop_count"] = 0
            print(config["game"]["day"])
            pop.communityMove()



        # Flip the display (refresh the screen)
        pygame.display.flip()

#___ END GAME LOOP ____________________________________________________________
# Done! Time to quit.
    pygame.quit()