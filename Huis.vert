
uniform mat4 ProjViewModel;

attribute vec4 vPosition;     

void main()                  
{  
	mat4 hallo = mat4(1.0);
	gl_Position = ProjViewModel * vPosition;  
    
}                            
