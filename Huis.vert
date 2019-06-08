precision highp float;
uniform mat4 ProjViewModel;

attribute vec4 vPosition;
attribute vec2 vExtra;

varying vec3 col;

void main()                  
{  
	gl_Position = ProjViewModel * vPosition;  

	col = (0.5 * vec3(sin(vExtra.x) * cos(vExtra.y), cos(vExtra.x) * cos(vExtra.y), sin(vExtra.y))) + vec3(0.5);
}                            
