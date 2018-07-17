plugins {
    application
}

application {

}

dependencies {
    implementation("org.jetbrains:annotations:16.0.2")
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.2.0")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:5.2.0")
}

tasks.withType<Test> {
    useJUnitPlatform()
}
