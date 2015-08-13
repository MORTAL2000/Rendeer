
//
// This file only contains purely functional functions. The functions are simply
// helper functions that performs some calculation that should be consistent
// between different shaders.
//

#ifndef _FUNCTIONS_GLSL
#define _FUNCTIONS_GLSL

vec3 encodeNormal(in vec3 normal)
{
	return normal * 0.5 + 0.5;
}

vec3 decodeNormal(in vec3 encodedNormal)
{
	return encodedNormal * 2.0 - 1.0;
}

float lambertianFactor(in vec3 surfaceNormal, in vec3 lightDirection)
{
	return max(dot(normalize(surfaceNormal), normalize(-lightDirection)), 0.0);
}

// Will make v1 ortagonal to v0. v1 will remain unchanged
void reortogonalize(in vec3 v0, inout vec3 v1)
{
	// Perform Gram-Schmidt's re-ortogonalization process
	v1 = normalize(v1 - dot(v1, v0) * v0);
}

mat3 makeTbnMatrix(in vec3 normal, in vec3 tangent)
{
	normalize(normal);
	normalize(tangent);
	reortogonalize(normal, tangent);
	vec3 biTangent = normalize(cross(normal, tangent));
	return mat3(tangent, biTangent, normal);
}

#define SHADOW_MAP_BIAS 0.0025

float calculateShadowMapInfluence(in vec3 viewSpacePosition,
                                  in mat4 inverseViewSpace,
                                  in mat4 lightViewProjection,
                                  in sampler2D shadowMap)
{
	// Transform view-space to world-space
	vec4 worldSpacePosition = inverseViewSpace * vec4(viewSpacePosition, 1.0);

	// Transform world-space to light-space
	vec4 lightSpacePosition = lightViewProjection * worldSpacePosition;
	lightSpacePosition.xyz /= lightSpacePosition.w;

	// Transform to light-space to screen-space
	vec4 screenSpace = lightSpacePosition * 0.5 + 0.5;

	// Clamp projected depth, since if a fragment is outside the light camera area
	// it should not be in shadow: i.e. projecteddepth <= shadow map depth. For it
	// to be that, it can't be outside the shadow map range.
	// This has the same effect as "if(screenSpace.z > 1.0) return 0.0;"
	float currentFragmentDepth = min(screenSpace.z, 1.0);
	float shadowMapDepth = texture(shadowMap, screenSpace.xy).r;

	return step(currentFragmentDepth, shadowMapDepth + SHADOW_MAP_BIAS);
}

// TODO: How should this be handled?
//#define USE_MAX_LIGHT_RANGE

// Since we use 8-bit color depth, a value lower that 1/256 is not visible. Therefore
// we can find the max light range by solving x for:
// (1 / x*x) < (1.0 / 256.0) => +-16
#ifdef USE_MAX_LIGHT_RANGE
	#define ATTENUATION_MAX_LIGHT_RANGE 16.0
#else
	#define ATTENUATION_MAX_LIGHT_RANGE 999999.0
#endif

float attenuation(in float lightToFragDistance)
{
	return 1.0 / (lightToFragDistance * lightToFragDistance);
}

#endif // _FUNCTIONS_GLSL
