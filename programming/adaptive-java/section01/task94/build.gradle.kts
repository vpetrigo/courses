plugins {
    `java-library`
    application
}

java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
}

application {
    mainClassName = "Main"
}

dependencies {
    implementation("org.jetbrains:annotations:16.0.2")
    testImplementation("org.junit.jupiter:junit-jupiter-engine:5.3.2")
    testImplementation("org.junit.jupiter:junit-jupiter-params:5.3.2")
    testImplementation("org.junit.platform:junit-platform-launcher:1.3.2")
    testImplementation("org.junit.vintage:junit-vintage-engine:5.3.2")
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}

tasks.withType<Test> {
    useJUnitPlatform()
    testLogging {
        events("passed", "skipped", "failed")
    }
}

tasks.withType<Wrapper> {
    gradleVersion = "5.0"
}
