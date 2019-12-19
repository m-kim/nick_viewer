uniform sampler3D data;
uniform sampler1D transfer_func;
uniform vec3 light;
uniform vec3 eye;
uniform float stepsize;
uniform vec3 volExtentMin;
uniform vec3 volExtentMax;

void main()
{
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] =  gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_TexCoord[1] =  gl_TextureMatrix[1] * gl_MultiTexCoord1;
	gl_Position = ftransform();
} 
