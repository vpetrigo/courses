fun doSomethingStrangeWithCollection(collection: Collection<String>): Collection<String>? =
    collection.groupBy { it.length }.values.maxBy { it.size }