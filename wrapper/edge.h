#pragma once

#include "sdk_mesh.h"
#include "mark.h"
#include "iterator.h"
#include "vector.h"

#include <array>
#include <memory>

class TEdgeId
{
public:
	explicit TEdgeId(unsigned index);
	operator unsigned() const;

private:
	unsigned Index;
};

class TPolygon;
class TPoint;
class TMesh;

class TEdge
{
public:
	using TUserData = CLxUser_Edge;

	explicit TEdge(CLxUser_Edge& edge);
	TEdge(const TEdge& rhs) = delete;
	TEdge& operator=(const TEdge& rhs) = delete;
	TEdge(TEdge&& rhs) = delete;

	void SetMark(TMarkMode mark);
	bool TestMark(TMarkMode mark) const;
	TEdgeId Index() const;
	LXtEdgeID ID() const;
	std::array<LXtPointID, 2> EndpointsID() const;
	LXtPointID OtherPointID(LXtPointID id) const;

	using TPolygonIterator = TIterator<TEdge, TPolygon>;
	using TPolygonContainer = TContainer<TEdge, TPolygon>;

	using TPointIterator = TIterator<TEdge, TPoint>;
	using TPointContainer = TContainer<TEdge, TPoint>;

	unsigned PolygonCount() const;
	unsigned Count(CLxUser_Polygon* p) const;
	TPolygon Get(CLxUser_Polygon* p, unsigned index);

	unsigned Count(CLxUser_Point* p) const;
	TPoint Get(CLxUser_Point* p, unsigned index);

	bool CheckNGon();
	bool IsManifold() const;
	float CalcFaceAngle();
	float Length() const;
	TVectorF ToVector() const;

	TPolygonContainer Polygons();
	TPointContainer Points();

	void Init(CLxUser_Polygon* polygon) const;
	void Init(CLxUser_Point* point) const;

    bool operator==(const TEdge& rhs) const;
    bool operator!=(const TEdge& rhs) const;

	bool Test() const;
private:
	CLxUser_Edge& Edge;
};

class TMesh;

class TEdgeHolder : public TEdge {
public:
    TEdgeHolder(TMesh& mesh, LXtEdgeID id);
    TEdgeHolder(TMesh& mesh, LXtPointID id1, LXtPointID id2);

private:
    CLxUser_Edge UserEdge_;
};
