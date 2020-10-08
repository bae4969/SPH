Fluid Simulator with SPH

///////////////////////////////////////////////////////////////////////////////////////////////

- Shading

in top of the grapic/main_G.cpp

when define "SPHERE_SHADING", it just use plane shading.

when define "VOLUME_SHADING", it use volume shading with threshold.

///////////////////////////////////////////////////////////////////////////////////////////////

- Keyboard Inputs

q, w, e, a, s, d		:	camera movement

z, c			:	zoom in out

x(SPHERE_SHADING)	:	change the terrain color, blue means high and red means low

p			:	pause the simulator

o			:	do not generate particles

n			:	show the number of particles

t			:	enable/disable showing terrain

','(<), '.'(>)		:	change the quality of simulator /  quality up -> simulator slow / quality down -> simulator fast 
