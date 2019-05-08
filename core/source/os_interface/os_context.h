namespace L0 {

class OsContext {
  public:
    OsContext() {}

    static OsContext *create(void *execEnvRT);
};

} // namespace L0
