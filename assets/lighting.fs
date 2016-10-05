#version 330

in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPos0;

const int MAX_POINT_LIGHT = 8;
const int MAX_SPOT_LIGHT = 4;

// baselight
struct BaseLight{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

// 方向光
struct DirectionalLight{
    BaseLight base;
    vec3 direction;
};

struct Attenuation{
    float constant;
    float linear;
    float expo;
};

// 点光源
struct PointLight{
    BaseLight base;
    vec3 position;
    Attenuation atten;
};

// 聚光灯
struct SpotLight{
    PointLight base;
    vec3 direction;
    float cutOff;
};


uniform sampler2D gSampler;
uniform DirectionalLight gDirectionalLight; // 方向光

//  镜面反射
uniform vec3 gEyeWorldPos;
uniform float gSpecularIntensity;
uniform float gSpecularPower;
uniform int gNumPointLights; // 点光源的个数
uniform PointLight gPointLights[MAX_POINT_LIGHT]; // 点光源

uniform int gNumSpotLights; // 聚光灯的个数
uniform SpotLight gSpotLights[MAX_SPOT_LIGHT];

out vec4 outFragColor;

#if 1

// 计算基本的 环境光  散射光  反射光
// 要求输入的 lightDir 和  normal 都已经规格化
vec4 calculateBaseLight(BaseLight light,vec3 lightDir,vec3 normal){
    
    // 环境光
    vec4 ambientColor = vec4(light.color * light.ambientIntensity,1.0);
    
    // 下面计算散射和反射
    float diffuseFactor = dot(normal,-lightDir);
    
    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);
    
    if (diffuseFactor > 0) {
        diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor,1.0);
        
        vec3 posToEye = normalize(gEyeWorldPos - WorldPos0);
        vec3 lightReflect = normalize(reflect(lightDir,normal));
        float specularFactor = dot(posToEye,lightReflect);
        if (specularFactor > 0) {
            specularFactor = pow(specularFactor,gSpecularPower);
            specularColor = vec4(light.color * gSpecularIntensity * specularFactor,1.0);
        }
    }
    
    return (ambientColor + diffuseColor + specularColor);
}

// 计算方向光
vec4 calculateDirLight(vec3 normal){
    return calculateBaseLight(gDirectionalLight.base,gDirectionalLight.direction,normal);
}

// 计算点光源
vec4 calculatePointLight(PointLight light,vec3 normal){
    vec3 lightDir = WorldPos0 - light.position;
    float dis = length(lightDir);
    lightDir = normalize(lightDir);
    
    vec4 color = calculateBaseLight(light.base,lightDir,normal);
    float attenuation = light.atten.constant +
    light.atten.linear * dis + light.atten.expo * dis * dis;
    return color/attenuation;
}

// 计算聚光灯
vec4 calculateSpotLight(SpotLight light,vec3 nor){
    vec3 lightToPixel = normalize(WorldPos0 - light.base.position);
    float spotFactor = dot(lightToPixel, light.direction);
    if (spotFactor > light.cutOff) {
        vec4 color = calculatePointLight(light.base, nor);
        return color * (1.0 - (1.0 - spotFactor) *
                         1.0/(1.0 - light.cutOff));
    }else {
        return vec4(0,0,0,0);
    }
}

#endif

void main()
{
#if 1
    vec3 normal = normalize(Normal0);
    vec4 totalLight = calculateDirLight(normal);
    
    for (int i = 0; i < gNumPointLights; ++i) {
        totalLight += calculatePointLight(gPointLights[i],normal);
    }
    
    for (int i = 0; i < gNumSpotLights; ++i) {
        totalLight += calculateSpotLight(gSpotLights[i],normal);
    }
    
    outFragColor = texture(gSampler,TexCoord0.xy) * totalLight;
#endif
    
#if 0
    // 环境光
    vec4 ambientColor = vec4(gDirectionalLight.base.color * gDirectionalLight.base.ambientIntensity,1.0);
    
    vec3 nor = normalize(Normal0);
    
    // 方向光
    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);
    
    float diffuseFactor = max(0.0,dot(nor,-gDirectionalLight.direction));
    if (diffuseFactor > 0) {
        diffuseColor = vec4(gDirectionalLight.base.color * gDirectionalLight.base.diffuseIntensity * diffuseFactor,1.0);
        
        vec3 posToEye = normalize(gEyeWorldPos - WorldPos0);
        vec3 lightReflect = normalize(reflect(gDirectionalLight.direction,nor));
        float specularFactor = dot(posToEye,lightReflect);
        if (specularFactor > 0) {
            specularFactor = pow(specularFactor,gSpecularPower);
            specularColor = vec4(gDirectionalLight.base.color * gSpecularIntensity * specularFactor,1.0);
        }
    }
    
    gl_FragColor = texture2D(gSampler,TexCoord0) * (ambientColor + diffuseColor + specularColor);
#endif

}
