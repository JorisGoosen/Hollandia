   
precision mediump float;
varying vec4 vPos;    

void main()                                  	
{            
		     
  	gl_FragColor = vPos * vec4 ( 1.0 );
	gl_FragColor.x = 1.0;                             
}                                            