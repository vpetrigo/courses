plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week05.task02.HashMapBuilderKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("org.junit.jupiter:junit-jupiter-api:5.2.0")
}
