//#define USE_TRANSFER

uniform sampler3D data;
uniform sampler1D transfer_func;
uniform sampler2D tex_ray_end;
uniform vec4 eye_viewport;
uniform vec3 stepsize;

bool isOutsideVolume(vec3 position,
		vec3 _volExtentMin,
		vec3 _volExtentMax)
{
	vec3 temp1 = sign(position - _volExtentMin);
	vec3 temp2 = sign(_volExtentMax - position);
	float inside = dot(temp1, temp2);
	return inside < 3.0;
}
vec4 colorBlend(vec4 src, vec4 dst) {
	vec4 result = dst;
	result.rgb   += src.rgb*(1.0-dst.a)*src.a;
	result.a     += (1.0-dst.a)*src.a;
	return result;
}

void main()
{
	vec4 value;
	float scalar;
	vec4 dst;
	dst = vec4(0,0,0,0);

	vec2 coord = gl_FragCoord.xy / eye_viewport.zw;
	vec3 ray_end = texture(tex_ray_end, coord).xyz;

	vec3 ray_start = gl_Color.xyz;
	vec3 direction = ray_end - ray_start;
	vec3 ray = vec3(0,0,0);

	float max_length = length(direction);
	direction = normalize(direction);
	vec3 step = direction * stepsize;

	for(int i=0; i<200; i++){
		value = texture3D(data, ray_start + ray);

		//GL_LUMINANCE will reside in value.r, g, or b
#ifdef USE_TRANSFER
		scalar = value.r;
		vec4 src = tex1D(transfer_func, scalar);

		//check for shadow
		vec3 shadow_direction = light - position;
		shadow_direction = normalize(shadow_direction);
		vec3 shadow_pos = position;
		if (dst.r > 0){
			while (!isOutsideVolume(shadow_pos, volExtentMin, volExtentMax)){
				vec4 shadow_value = tex3D(data,shadow_pos);
				if (shadow_value.r > 0){
					dst -= vec4(0.1,0.1,0.1,0.1);
					break;
				}
				shadow_pos = shadow_pos + direction * stepsize;
			}
		}
		dst = (1.0 - i * stepsize) * src + dst;
#else
		vec4 src;
		if (value.r < 0.5)
			src = vec4(0);
		else
			src = vec4(1);

		dst = colorBlend(src, dst);

#endif


		if (dst.a > 0.99 || length(ray) >= max_length)
		   break;

		ray += step;
	}

	gl_FragColor = dst;

}
