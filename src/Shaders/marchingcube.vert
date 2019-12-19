#version 130

out mat4 model_view_projection_matrix;
void main()
{	
	gl_Position = gl_Vertex;
	gl_FrontColor=gl_Color;

	model_view_projection_matrix = gl_ModelViewProjectionMatrix;
	
}

