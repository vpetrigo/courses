plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "task03.NamedArgsKt"
}

repositories {
    mavenCentral()
}

dependencies {
    compile(kotlin("stdlib"))
}
