
%extend Urho3D::HashIteratorBase
{
	%rename(__eq__) operator == (const HashIteratorBase&) const;
	%csmethodmodifiers operator == "private";
	
	%rename(__neq__) operator != (const HashIteratorBase&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::HashIteratorBase
%{
	public static bool operator == (HashIteratorBase a, HashIteratorBase b)
	{
		return a.__eq__(b);
	}

	public static bool operator != (HashIteratorBase a, HashIteratorBase b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::ListIteratorBase
{
	%rename(__eq__) operator == (const ListIteratorBase&) const;
	%csmethodmodifiers operator == "private";
	
	%rename(__neq__) operator != (const ListIteratorBase&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::ListIteratorBase
%{
	public static bool operator == (ListIteratorBase a, ListIteratorBase b)
	{
		return a.__eq__(b);
	}

	public static bool operator != (ListIteratorBase a, ListIteratorBase b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::SourceBatch
{
	%rename(__ieq__) operator = (const SourceBatch&);
	%csmethodmodifiers operator = "private";
};



%extend Urho3D::BatchGroupKey
{
	%rename(__eq__) operator == (const BatchGroupKey&) const;
	%csmethodmodifiers operator == "private";
	
	%rename(__neq__) operator != (const BatchGroupKey&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::BatchGroupKey
%{
	public static bool operator == (BatchGroupKey a, BatchGroupKey b)
	{
		return a.__eq__(b);
	}

	public static bool operator != (BatchGroupKey a, BatchGroupKey b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::VertexElement
{
	%rename(__eq__) operator == (const VertexElement&) const;
	%csmethodmodifiers operator == "private";
	
	%rename(__neq__) operator != (const VertexElement&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::VertexElement
%{
	public static bool operator == (VertexElement a, VertexElement b)
	{
		return a.__eq__(b);
	}

	public static bool operator != (VertexElement a, VertexElement b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::OctreeQueryResult
{
	%rename(__neq__) operator != (const OctreeQueryResult&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::OctreeQueryResult
%{
	public static bool operator != (OctreeQueryResult a, OctreeQueryResult b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::RayQueryResult
{
	%rename(__neq__) operator != (const RayQueryResult&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::RayQueryResult
%{
	public static bool operator != (RayQueryResult a, RayQueryResult b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::Spline
{
	%rename(__ieq__) operator = (const Spline&);
	%csmethodmodifiers operator = "private";

	%rename(__eq__) operator == (const Spline&) const;
	%csmethodmodifiers operator == "private";
	
	%rename(__neq__) operator != (const Spline&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::Spline
%{
	public static bool operator == (Spline a, Spline b)
	{
		return a.__eq__(b);
	}

	public static bool operator != (Spline a, Spline b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::BoundingBox
{
	%rename(__ieq__) operator = (const BoundingBox&);
	%rename(__ieq__) operator = (const Rect&);
	%csmethodmodifiers operator = "private";

	%rename(__eq__) operator == (const BoundingBox&) const;
	%csmethodmodifiers operator == "private";
	
	%rename(__neq__) operator != (const BoundingBox&) const;
	%csmethodmodifiers operator != "private";
};

%typemap(cscode) Urho3D::BoundingBox
%{
	public static bool operator == (BoundingBox a, BoundingBox b)
	{
		return a.__eq__(b);
	}

	public static bool operator != (BoundingBox a, BoundingBox b)
	{
		return a.__neq__(b);
	}
%}


%extend Urho3D::Frustum
{
	%rename(__ieq__) operator = (const Frustum&);
	%csmethodmodifiers operator = "private";
};
