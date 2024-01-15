#pragma once
#include "Hitable.h"
#include <memory>
#include <vector>

using namespace std;

class HittableCollection : public Hittable
{
private:
	vector<shared_ptr<Hittable>> mPool;
public:
	HittableCollection() = default;
	HittableCollection(shared_ptr<Hittable> hittable) { Add(hittable); }

	void Clear() { mPool.clear(); }
	void Add(shared_ptr<Hittable> hittable) { mPool.push_back((hittable)); }

	bool Hit(const Ray& rRay, Interval rayTime, HitInfo& hitInfo) const override;
};