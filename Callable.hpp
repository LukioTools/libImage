namespace Image
{
    template<typename Ret = void, typename ...T>
    struct Callable
    {
            ///sad itll prolly be unused
        Ret operator()(T... args){
            call(args...);
        }
        virtual Ret call(T... args){return {};}
    };

    template<typename Ret = void, typename ...T>
    struct Basic_Fn : public Callable<Ret, T...>
    {
        Ret(*fn)(T...) = nullptr;
        Ret call(T...args) override{
            return fn(args...);
        }
        Basic_Fn() = default;
        Basic_Fn(Ret(*fn)(T...)): fn(fn){};
    };
    
} // namespace Image
