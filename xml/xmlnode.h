/**
 * XML Node Object
 */
class XMLNode
{
public:
   typedef XMLNode                           self_type;
   typedef std::string                       string_type;
   typedef std::map<string_type,string_type> attribute_map_type;
   typedef std::map<string_type,self_type*>  children_type;

   /**
    * Default constructor
    */
   XMLNode() :
      _parent(0)
   {}
   
   /**
    * Constructor from a tag
    */
   XMLNode(const string_type& tag) :
      _tag(tag),
      _parent(0)
   {}
   
   /**
    * Copy constructor
    */
   XMLNode(const XMLNode& other) :
      _tag(other._tag),
      _parent(other._parent),
      _children(other._children),
      _attributes(other._attributes)
   {}
   
   /**
    * Destructor
    */
   virtual ~XMLNode() {}
   
   /**
    * Assignment operator
    */
   self_type& operator=(const self_type& rhs)
   {
      if( &rhs != this )
      {
         _tag        = rhs._tag;
         _parent     = rhs._parent;
         _children   = rhs._children;
         _attributes = rhs._attributes;
      return *this;
   }

protected:
   string_type _tag;
   self_type* _parent;
   children_type _children ;
   attribute_map_type _attributes;
};
