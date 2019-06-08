attribute vec4 vPosition;    
varying vec4 vPos;    

void main()                  
{                            
   gl_Position = vPosition;  
   vPos = vPosition; 
}                            
