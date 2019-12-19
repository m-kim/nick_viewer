#version 120
#extension GL_EXT_geometry_shader4 : enable 
#extension GL_EXT_gpu_shader4 : enable 
 

uniform sampler3D dataFieldTex; 
uniform isampler2D edgeTableTex; 
uniform isampler2D triTableTex; 
uniform float isolevel; 
uniform vec3 vertDecals[8]; 


varying vec4 position_out;
varying vec4 normal_out;

//Get vertex i position within current marching cube 
vec3 cubePos(int i){ 
    return gl_PositionIn[0].xyz + vertDecals[i]; 
} 
 
//Get vertex i value within current marching cube 
float cubeVal(int i){ 
    //return texture(dataFieldTex, (cubePos(i)+1.0f)/2.0f).a;
	return texture3D(dataFieldTex, cubePos(i)).r;
} 
 
//Get triangle table value 
int triTableValue(int i, int j){ 
    return texelFetch(triTableTex, ivec2(j, i), 0).a; 
} 
 
//Compute interpolated vertex along an edge 
vec3 vertexInterp(float isolevel, vec3 v0, float l0, vec3 v1, float l1){ 
    return mix(v0, v1, (isolevel-l0)/(l1-l0)); 
} 
 
//Geometry Shader entry point 
void main(void) { 
	
    int cubeindex=0; 
    float cubeVal0 = cubeVal(0); 
    float cubeVal1 = cubeVal(1); 
    float cubeVal2 = cubeVal(2); 
    float cubeVal3 = cubeVal(3); 
    float cubeVal4 = cubeVal(4); 
    float cubeVal5 = cubeVal(5); 
    float cubeVal6 = cubeVal(6); 
    float cubeVal7 = cubeVal(7); 
 
    //Determine the index into the edge table which 
    //tells us which vertices are inside of the surface 
    cubeindex = int(cubeVal0 < isolevel); 
    cubeindex += int(cubeVal1 < isolevel)*2; 
    cubeindex += int(cubeVal2 < isolevel)*4; 
    cubeindex += int(cubeVal3 < isolevel)*8; 
    cubeindex += int(cubeVal4 < isolevel)*16; 
    cubeindex += int(cubeVal5 < isolevel)*32; 
    cubeindex += int(cubeVal6 < isolevel)*64; 
    cubeindex += int(cubeVal7 < isolevel)*128; 
 
//    gl_FrontColor = vec4(float(cubeindex) / 255.f);
//    gl_Position = gl_ModelViewProjectionMatrix* vec4(0,0,0,1); 
//    EmitVertex(); 
//    gl_Position = gl_ModelViewProjectionMatrix* vec4(1,0,0,1); 
//    EmitVertex(); 
//    gl_Position = gl_ModelViewProjectionMatrix* vec4(0,1,0,1); 
//    EmitVertex(); 
//    EndPrimitive();

    //Cube is entirely in/out of the surface 
    if (cubeindex ==0 || cubeindex == 255) 
        return; 
 
    vec3 vertlist[12]; 
    //Find the vertices where the surface intersects the cube 
    vertlist[0] = vertexInterp(isolevel, cubePos(0), cubeVal0, cubePos(1), cubeVal1); 
    vertlist[1] = vertexInterp(isolevel, cubePos(1), cubeVal1, cubePos(2), cubeVal2); 
    vertlist[2] = vertexInterp(isolevel, cubePos(2), cubeVal2, cubePos(3), cubeVal3); 
    vertlist[3] = vertexInterp(isolevel, cubePos(3), cubeVal3, cubePos(0), cubeVal0); 
    vertlist[4] = vertexInterp(isolevel, cubePos(4), cubeVal4, cubePos(5), cubeVal5); 
    vertlist[5] = vertexInterp(isolevel, cubePos(5), cubeVal5, cubePos(6), cubeVal6); 
    vertlist[6] = vertexInterp(isolevel, cubePos(6), cubeVal6, cubePos(7), cubeVal7); 
    vertlist[7] = vertexInterp(isolevel, cubePos(7), cubeVal7, cubePos(4), cubeVal4); 
    vertlist[8] = vertexInterp(isolevel, cubePos(0), cubeVal0, cubePos(4), cubeVal4); 
    vertlist[9] = vertexInterp(isolevel, cubePos(1), cubeVal1, cubePos(5), cubeVal5); 
    vertlist[10] = vertexInterp(isolevel, cubePos(2), cubeVal2, cubePos(6), cubeVal6); 
    vertlist[11] = vertexInterp(isolevel, cubePos(3), cubeVal3, cubePos(7), cubeVal7); 
 
    // Create the triangle 
//    gl_FrontColor=vec4(cos(isolevel*5.0-0.5), sin(isolevel*5.0-0.5), 0.5, 1.0);
    int i=0;  
    //Strange bug with this way, uncomment to test 
    //for (i=0; triTableValue(cubeindex, i)!=-1; i+=3) {
    while(true){         
        gl_FrontColor = gl_FrontColorIn[i % 3];
        if(triTableValue(cubeindex, i)!=-1){ 
        	position_out = vec4(vertlist[triTableValue(cubeindex, i)], 1); 
            gl_Position = gl_ModelViewProjectionMatrix* position_out; 
            EmitVertex(); 
        	position_out = vec4(vertlist[triTableValue(cubeindex, i+1)], 1); 
            gl_Position = gl_ModelViewProjectionMatrix*position_out; 
            EmitVertex(); 
        	position_out = vec4(vertlist[triTableValue(cubeindex, i+2)], 1); 
            gl_Position = gl_ModelViewProjectionMatrix* position_out; 
            EmitVertex(); 
            EndPrimitive(); 
        }else{ 
            break; 
        } 
        i=i+3; //Comment it for testing the strange bug 
    } 
}
