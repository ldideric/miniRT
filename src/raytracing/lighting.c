/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/15 10:10:47 by ldideric      #+#    #+#                 */
/*   Updated: 2020/09/15 10:16:18 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

Vec3f castRay(const Vec3f &orig, const Vec3f &dir, const std::vector<std::unique_ptr<Object>> &objects, const std::unique_ptr<DistantLight> &light, const Options &options)
{
	Vec3f hitColor = options.backgroundColor;
	IsectInfo isect;
	if (trace(orig, dir, objects, isect)) {
		Vec3f hitPoint = orig + dir * isect.tNear;
		Vec3f hitNormal;
		Vec2f hitTexCoordinates;
		isect.hitObject->getSurfaceProperties(hitPoint, dir, isect.index, isect.uv, hitNormal, hitTexCoordinates);
		Vec3f L = -light->dir;
		IsectInfo isectShad;
		bool vis = !trace(hitPoint + hitNormal * options.bias, L, objects, isectShad, kShadowRay);
		hitColor = vis * isect.hitObject->albedo * light->intensity * light->color * std::max(0.f, hitNormal.dotProduct(L));
	}

	return hitColor; 
}
