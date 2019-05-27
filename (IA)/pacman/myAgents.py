from pacman import Directions
from game import Agent
import random
import game
import util
import time





class papatudo(Agent):
	def getAction(self, estado):
		"""
			procura comida e papa
		"""
		
		pos = estado.getPacmanPosition()
		opcoes = estado.getLegalPacmanActions()
		
		print time.time()
		
		wt = estado.hasFood(pos[0]-1,pos[1])
		et = estado.hasFood(pos[0]+1,pos[1])
		nt = estado.hasFood(pos[0],pos[1]-1)
		st = estado.hasFood(pos[0],pos[1]+1)
		
		if ('West' in opcoes) and wt: return 'West'
		if ('East' in opcoes) and et: return 'East'
		if ('North' in opcoes) and nt: return 'North'
		if ('South' in opcoes) and st: return 'South'
		
		
		#if 'East' in opcoes: return 'East'
		if 'South' in opcoes: return 'South'
		
		#return random.choice(opcoes)




class snakepath(Agent):
  def getAction(self, state):
  	"""
  		python pacman.py -p snakepath -l openSearch
  	"""
  	if 'path' not in dir(self): self.path = -1
  	dr = ['North','South','East','West','Stop']
  	i = [
  		2,1,3,1,2,2,2,2,0,0,
  		2,1,1,2,2,2,2,0,3,0,
  		2,0,0,3,1,3,1,1,3,0,
  		0,3,3,3,1,1,3,0,0,3,
  		3,3,3,3,1,1,2,0,2,1,
  		1,3,3,3,0,3,1,3,0,3,
  		1,3,0,0,2,0,3,0,2,2,
  		1,1,2,2,0,3,0,2,2,2,
  		2,2,2,2,2,2,2,2,2,4
  	]
  	self.path += 1
  	return  dr[i[self.path]]
  	


class esquerda(Agent):
  def getAction(self, state):
  	print state.getLegalPacmanActions()
  	print
  	
  	opcoes = state.getLegalPacmanActions()
  	
  	successors = [(state.generateSuccessor(0, ato), ato) for ato in opcoes]
  		
  	pontuado = [(estado.getScore(), ato) for estado, ato in successors]
  	
  	
  	maispontuado = max(pontuado)[0]
  	melhores = [par[1] for par in pontuado if par[0] == maispontuado]
  	
  	return random.choice(melhores)



    
    





  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  